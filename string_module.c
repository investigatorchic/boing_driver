/*
 * xlate_module.c - Device driver module for xlate device.
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

static d_open_t		xlate_open;
static d_close_t	xlate_close;
static d_read_t		xlate_read;
static d_write_t	xlate_write;
static d_ioctl_t	xlate_ioctl;

static struct cdev *sdev;

static struct cdevsw xlate_cdevsw = {
	.d_version =	D_VERSION,
	.d_open =	xlate_open,
	.d_close =	xlate_close,
	.d_read =	xlate_read,
	.d_write =	xlate_write,
	.d_ioctl =	xlate_ioctl,
	.d_name =	"xlate",
};

static int
xlate_open(struct cdev *dev, int flag, int mode, struct thread *td)
{
#ifdef XLATE_DEBUG
	uprintf("xlate_open() called\n");
#endif
	return(0);
}

static int
xlate_close(struct cdev *dev, int flag, int mode, struct thread *td)
{
#ifdef XLATE_DEBUG
	uprintf("xlate_close() called\n");
#endif
	return(0);
}

static int
xlate_read(struct cdev *dev, struct uio *uio, int flags)
{
#ifdef XLATE_DEBUG
	uprintf("xlate_read() called\n");
#endif
	return(0);
}

static int
xlate_write(struct cdev *dev, struct uio *uio, int flags)
{
#ifdef XLATE_DEBUG
	uprintf("xlate_write() called\n");
#endif
	return(0);
}

static int
xlate_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int flag, struct thread *td)
{
#ifdef XLATE_DEBUG
	uprintf("xlate_ioctl() called\n");
#endif
	return(0);
}

static int
xlate_load(module_t mod, int what, void *arg)
{
#ifdef XLATE_DEBUG
	uprintf("xlate_load() called\n");
#endif
	int error = 0;
	switch(what) {
		case MOD_LOAD:
			sdev = make_dev(&xlate_cdevsw, 0, UID_ROOT, GID_WHEEL,
				0666, "xlate");
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

DEV_MODULE(xlate_module, xlate_load, NULL);
