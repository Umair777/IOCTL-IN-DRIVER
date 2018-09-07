#include"header.h"
#include"declarations.h"
int trimdev(Dev *ldev)
{
	Qset *last,*slast;
	int j;
	last = NULL;
	slast = NULL;
#ifdef DEBUG
	printk(KERN_ALERT "trimdev Begins\n");
#endif
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_ERR "Device not found\n");
#endif	
	}
	if(!ldev->first)
	{
#ifdef DEBUG
		printk(KERN_ERR "No item found to trim\n");
#endif	
	}
	else
	{
		last=slast=ldev->first;
		while(ldev->first)
		{
			printk(KERN_INFO "==========\n");
			last=slast=ldev->first;
			while(last->next != NULL)
			{
				slast=last;
				last=slast->next;	
			}
			if(last->data)
			{
			for(j=noofreg-1;j>=0;j--)
			{
				printk(KERN_INFO "j =%d\n",j);
				kfree(last->data[j]);
				last->data[j]=NULL;
			}
			kfree(last->data);
			last->data=NULL;
			}
		}
	}
#ifdef DEBUG
	printk(KERN_ALERT "trimdev Ends\n");
#endif
	return 0;
}
