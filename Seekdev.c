#include"header.h"
#include"declarations.h"
loff_t Seekdev(struct file *filep,loff_t offset,int origin)
{
Dev * ldev;
#ifdef DEBUG
	printk(KERN_ALERT "Seekddev Begins\n");
#endif
#ifdef DEBUG
	printk(KERN_INFO "value of offset:%ld\n",(long int)filep->f_pos);
#endif
	ldev=filep->private_data;
	if(!ldev)
	{
#ifdef DEBUG
	printk(KERN_INFO "ldev failed in Seekdev\n");
#endif
	}		
	switch(origin)
	{
	case 0:
		if(offset>ldev->devsize)
		{
#ifdef DEBUG
	printk(KERN_INFO "limit is exceeded\n");
#endif
	goto OUT;
		}
		filep->f_pos=offset;
		break;
	case 1:
		break;
	case 2:
		break;
	}	
#ifdef DEBUG
	printk(KERN_INFO "value of offset:%ld\n",(long int)filep->f_pos);
#endif
#ifdef DEBUG
	printk(KERN_ALERT "Seekdev Ends\n");
#endif
	return filep->f_pos;
OUT:
#ifdef DEBUG
	printk(KERN_ALERT "Error has occured in Seekdev\n");
	return -1;
#endif
}
