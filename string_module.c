/*
 * string_module.c - Device driver module for string device.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/module.h>
#include <sys/proc.h>
#include <sys/mutex.h>

#define MAX_BUFFER 50
#define DEFAULT_MSG "Hello World."
MALLOC_DEFINE(M_STRBUF, "string_buffer", "data storage for /dev/string");

static d_open_t		string_open;
static d_close_t	string_close;
static d_read_t		string_read;
static d_write_t	string_write;
static d_ioctl_t	string_ioctl;

static struct cdev *sdev;

static struct cdevsw string_cdevsw = {
	.d_version =	D_VERSION,
	.d_open =	string_open,
	.d_close =	string_close,
	.d_read =	string_read,
	.d_write =	string_write,
	.d_ioctl =	string_ioctl,
	.d_name =	"string",
};
static char *message;
static int locked=0;
static int buf_length=0;
static struct mtx slock;

static int
string_open(struct cdev *dev, int flag, int mode, struct thread *td)
{
#ifdef STRING_DEBUG
	uprintf("string_open() called\n");
#endif
	mtx_lock(&slock);
	if (locked) {
		mtx_unlock(&slock);
		return EPERM;
	}
	locked++;
	mtx_unlock(&slock);
	return(0);
}

static int
string_close(struct cdev *dev, int flag, int mode, struct thread *td)
{
#ifdef STRING_DEBUG
	uprintf("string_close() called\n");
#endif
	int result = EBADF;
	mtx_lock(&slock);
	if (locked) {
		locked--;
		result = 0;
	}
	mtx_unlock(&slock);
	return(result);
}

static int
string_read(struct cdev *dev, struct uio *uio, int flags)
{
#ifdef STRING_DEBUG
	uprintf("string_read() called\n");
#endif

	int result = 0, size;
	int data_available = 0;
  	if ( buf_length - uio->uio_offset > 0 ) {
    		data_available = buf_length - uio->uio_offset;
  	}
  	size = MIN(uio->uio_resid, data_available);
	result = uiomove(message + uio->uio_offset, size, uio);
	return result;
}

static int
string_write(struct cdev *dev, struct uio *uio, int flags)
{
#ifdef STRING_DEBUG
	uprintf("string_write() called\n");
#endif
	int result = 0;
	int data_available = 0;
	if ( MAX_BUFFER-1 - uio->uio_offset > 0 ) {
                data_available = MAX_BUFFER-1 - uio->uio_offset;
        }
	if (data_available == 0)
                return result;

	if (data_available > MAX_BUFFER) {
		return EPERM;
	}
	data_available = MIN(uio->uio_resid, data_available);	
	result = uiomove(message, data_available, uio);
	if (result) {
		return result;
	}
	message[data_available] = '\0';
	buf_length = data_available;
        return result;
}

static int
string_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int flag, struct thread *td)
{
#ifdef STRING_DEBUG
	uprintf("string_ioctl() called\n");
#endif
	return(0);
}

static int
string_load(module_t mod, int what, void *arg)
{
#ifdef STRING_DEBUG
	uprintf("string_load() called\n");
#endif
	int error = 0;
	switch(what) {
		case MOD_LOAD:
			message = malloc(MAX_BUFFER, M_STRBUF, M_WAITOK);
			if (message) {
			mtx_init(&slock, "string_lock", NULL, MTX_DEF);
			sdev = make_dev(&string_cdevsw, 0, UID_ROOT, GID_WHEEL,
				0666, "string");
			buf_length = strlen(DEFAULT_MSG);
			strncpy(message, DEFAULT_MSG, buf_length);
			}
			else {
			error = ENOMEM;
			}
			break;
		case MOD_UNLOAD:
			if (message) free(message, M_STRBUF);
			mtx_destroy(&slock);
			destroy_dev(sdev);
			break;
		default:
			error = EINVAL;
			break;
	}
	return(error);
}

DEV_MODULE(string_module, string_load, NULL);
