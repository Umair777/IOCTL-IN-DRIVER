#include"header.h"
#include"declarations.h"
ssize_t Readdev(struct file *filep,char __user *ubuff,size_t size,loff_t *offp)
{
	int read_beg_i,read_beg_qs,quantum,k;
	int ret,noctr,nocsr,i;
	Dev *ldev;
	Qset *lqset;
	size_t lsize;
	loff_t offset;
#ifdef DEBUG
	printk(KERN_ALERT "Readdev Begins\n");
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
		printk(KERN_INFO "Device couldn't be found\n");
		return (ssize_t)-1;
#endif
	}
	if(size>ldev->datasize)
	{
		lsize=ldev->datasize;	
#ifdef DEBUG
		printk(KERN_ERR "Partial writing of data will be done\n");
#endif
	}
	else
	{
		lsize=size;
	}
	printk(KERN_INFO "lsize:%d\n",(int)lsize);
	lqset=ldev->first;
	printk(KERN_INFO "address of first item received by readdev is :%p\n",ldev->first);
	offset=filep->f_pos;
	read_beg_i=offset/(noofreg*regsize);
	if(offset%(noofreg*regsize)!=0)
	{
		read_beg_i++;
	}
#ifdef DEBUG
	printk(KERN_INFO "read_beg_i:%d\n",read_beg_i);
#endif
	read_beg_qs=offset/regsize;
#ifdef DEBUG
	printk(KERN_INFO "read_beg_qs:%d\n",read_beg_qs);
#endif
	for(k=0;k<read_beg_i;k++)
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
	noctr=lsize;
	nocsr=0;
	quantum=(read_beg_qs+1)%noofreg;
	i=quantum-1;
	while(noctr)
	{
		if(noctr > ldev->regsize)
		{
			noctr=ldev->regsize;
		}
		ret=copy_to_user(ubuff+nocsr,lqset->data[i],noctr);	
		if(ret)
		{
#ifdef DEBUG
			printk(KERN_ERR "Partial reading taking place\n");
#endif
		}
		nocsr+=noctr-ret;
		*offp+=noctr-ret;
		noctr=lsize-nocsr;
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
	filep->f_pos=*offp;
#ifdef DEBUG
        printk(KERN_INFO "Offset is: %ld\n",(long int)*offp);
#endif
#ifdef DEBUG
        printk(KERN_INFO "f_pos is: %ld\n",(long int)filep->f_pos);
#endif
#ifdef DEBUG
	printk(KERN_ALERT "Readdev Ends\n");
#endif
	return nocsr;
}
