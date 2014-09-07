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
char *message = "Hello World.";
static int
string_open(struct cdev *dev, int flag, int mode, struct thread *td)
{
#ifdef STRING_DEBUG
	uprintf("string_open() called\n");
#endif
	return(0);
}

static int
string_close(struct cdev *dev, int flag, int mode, struct thread *td)
{
#ifdef STRING_DEBUG
	uprintf("string_close() called\n");
#endif
	return(0);
}

static int
string_read(struct cdev *dev, struct uio *uio, int flags)
{
#ifdef STRING_DEBUG
	uprintf("string_read() called\n");
#endif

	char *ptr;

	if(uio->uio_offset >= strlen(message))
		return(0);
	ptr = message;
	ptr += uio->uio_offset;
	return(uiomove(ptr, strlen(ptr) + 1, uio));

}

static int
string_write(struct cdev *dev, struct uio *uio, int flags)
{
#ifdef STRING_DEBUG
	uprintf("string_write() called\n");
#endif
	return(0);
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
			sdev = make_dev(&string_cdevsw, 0, UID_ROOT, GID_WHEEL,
				0666, "string");
			break;
		case MOD_UNLOAD:
			destroy_dev(sdev);
			break;
		default:
			error = EINVAL;
			break;
	}
	return(error);
}

DEV_MODULE(string_module, string_load, NULL);
