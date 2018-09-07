#include"header.h"
#include"declarations.h"
ssize_t Writedev(struct file *filep,const char __user *ubuff,size_t size,loff_t *offp)
{
	int write_beg_i,write_beg_qs,quantum,k;
	int ret,noctw,nocsw,i;
	Dev *ldev;
	Qset *lqset;
	size_t lsize;
	loff_t offset;
#ifdef DEBUG
	printk(KERN_ALERT "Writedev Begins\n");
#endif
#ifdef DEBUG
	printk(KERN_INFO "Offset is: %ld\n",(long int)*offp);
#endif
#ifdef DEBUG
	printk(KERN_INFO "f_pos is: %ld\n",(long int)filep->f_pos);
#endif
	ldev=filep->private_data;	
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_INFO "ldev failed\n");
#endif
	}
	if(size>ldev->devsize)
	{
		lsize=ldev->devsize;	
#ifdef DEBUG
		printk(KERN_ERR "Partial writing of data will be done\n");
#endif
	}
	else
	{
		lsize=size;
	}
	lqset=ldev->first=allocdev(lsize,filep->f_pos);
	printk(KERN_INFO "Address of first item received by writedev is:%p\n",lqset);
	offset=filep->f_pos;
	write_beg_i=offset/(noofreg*regsize);
	if(offset%(noofreg*regsize)!=0)
	{
		write_beg_i++;
	}
#ifdef DEBUG
	printk(KERN_INFO "write_beg_i:%d\n",write_beg_i);
#endif
	write_beg_qs=offset/regsize;
#ifdef DEBUG
	printk(KERN_INFO "write_beg_qs:%d\n",write_beg_qs);
#endif
	for(k=0;k<write_beg_i;k++)
	{
		if(k==0)
		{
			lqset=ldev->first;
		}
		else
		{
			lqset=lqset->next;	
		}
	}
	noctw=lsize;
	nocsw=0;
	quantum=(write_beg_qs+1)%noofreg;
	i=quantum-1;
	while(noctw)
	{
		if(noctw > ldev->regsize)
		{
			noctw=ldev->regsize;
	}
		ret=copy_from_user(lqset->data[i],ubuff+nocsw,noctw);	
		if(ret)
		{
#ifdef DEBUG
			printk(KERN_ERR "Partial writing taking place\n");
#endif
		}
		printk(KERN_INFO "data written :%s\n",(char *)lqset->data[i]);
		nocsw+=noctw-ret;
		*offp=*offp+noctw-ret;
		noctw=lsize-nocsw;
		if(i == ldev->noofreg-1 )
		{
			lqset=lqset->next;
			i=0;
		}
		else
		{
			i++;
		}
	}
	ldev->datasize=nocsw;
	filep->f_pos=*offp;
#ifdef DEBUG
	printk(KERN_INFO "Offset is: %ld\n",(long int)*offp);
#endif
#ifdef DEBUG
	printk(KERN_INFO "f_pos is: %ld\n",(long int)filep->f_pos);
#endif
#ifdef DEBUG
	printk(KERN_ALERT "Writedev Ends\n");
#endif
	return nocsw;
}
