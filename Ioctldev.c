#include"header.h"
#include"declarations.h"
#include"ioctl.h"
long ioctl_dev(struct file *filep,unsigned int cmd,unsigned long arg)
{
	Dev *ldev;
	//	Qset *lqset;
	//	size_t lsize;
	//	loff_t offset;
	int ret;
#ifdef DEBUG
	printk(KERN_ALERT "Ioctldev Begins\n");
#endif
	ldev=filep->private_data;	
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_INFO "ldev failed\n");
#endif
	}
	switch(cmd)
	{
		case GETREGSIZE:
			ret=put_user(ldev->regsize,(int __user *)arg);
			if(ret < 0)
			{
#ifdef DEBUG
				printk(KERN_ERR "Couldn't give appropriate value to user\n");
#endif
				goto OUT;
			}
			break;
		case GETNOOFREG:
			ret=put_user(ldev->noofreg,(int __user *)arg);
			if(ret < 0)
			{
#ifdef DEBUG
				printk(KERN_ERR "Couldn't give appropriate value to user\n");
#endif
				goto OUT;
			}
			break;
		case GETDEVICESIZE:
			ret=put_user(ldev->devsize,(int __user *)arg);
			if(ret < 0)
			{
#ifdef DEBUG
				printk(KERN_ERR "Couldn't give appropriate value to user\n");
#endif
				goto OUT;
			}
			break;
		case GETDATASIZE:
			ret=put_user(ldev->datasize,(int __user *)arg);
			if(ret < 0)
			{
#ifdef DEBUG
				printk(KERN_ERR "Couldn't give appropriate value to user\n");
#endif
				goto OUT;
			}
			break;
		case SETREGSIZE:
			ret=get_user(ldev->regsize,(int __user *)arg);
			if(ret < 0)
			{
#ifdef DEBUG
				printk(KERN_ERR "Couldn't give appropriate value to user\n");
#endif
				goto OUT;
			}
			break;
		case SETNOOFREG:
			ret=get_user(ldev->noofreg,(int __user *)arg);
			if(ret < 0)
			{
#ifdef DEBUG
				printk(KERN_ERR "Couldn't give appropriate value to user\n");
#endif
				goto OUT;
			}
			break;
		case DEVRESET:
	//		if(access_ok(VERIFY_WRITE,ldev,sizeof(Dev)))
	//		{
				ldev->noofreg=noofreg=16;
				ldev->regsize=regsize=8;
				ldev->devsize=devsize=128;
				ldev->datasize=datasize=0;
	//		}
			break;
		default:
			printk(KERN_ALERT "Wrong choice\n");
			goto OUT;
	}

#ifdef DEBUG
	printk(KERN_ALERT "Ioctldev Ends\n");
#endif
	return 0;
OUT:
#ifdef DEBUG
	printk(KERN_ERR "Error occured\n");
#endif
	return -1;
}
