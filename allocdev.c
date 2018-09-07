#include"header.h"
#include"declarations.h"
int noi,noq,i,j,k;
Qset *qset;
Qset *first;
Qset * allocdev(int fsize,loff_t offset)
{
	int t_size,write_beg_i,write_beg_qs,write_beg_q,quantum;
	t_size=fsize+offset;
#ifdef DEBUG
	printk(KERN_ALERT "Allocdev Begins\n");
#endif
#ifdef DEBUG
	printk(KERN_INFO "fsize:%d\n",fsize);
#endif
	noi=t_size/(noofreg*regsize);
	if(t_size%(noofreg*regsize)!=0)
	{
		noi++;
	}
#ifdef DEBUG
	printk(KERN_INFO "noi:%d\n",noi);
#endif
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
	write_beg_q=offset%regsize;
#ifdef DEBUG
	printk(KERN_INFO "write_beg_q:%d\n",write_beg_q);
#endif
	noq=fsize/(regsize);
	if(fsize%(regsize)!=0)
	{
		noq++;
	}
#ifdef DEBUG
	printk(KERN_INFO "noq:%d\n",noq);
#endif
	for(i=0;i<noi;i++)
	{
		if(i==0)
		{
			first=(Qset *)kmalloc(sizeof(Qset),GFP_KERNEL);
			qset=first;
			if(!first)
			{
#ifdef DEBUG
				printk(KERN_ERR "ldev->first ERROR\n");
#endif
				return (Qset *)-1;
			}
			memset(first,'\0',sizeof(Qset));
		}
		else
		{
			qset->next=(Qset*)kmalloc(sizeof(Qset),GFP_KERNEL);	
			if(!qset->next)
			{
#ifdef DEBUG
				printk(KERN_ERR "qset ERROR\n");
#endif
				return (Qset *)-1;
			}
			memset(qset->next,'\0',sizeof(Qset));	
			qset=qset->next;
			//		else
			//		{
			//		qset->next= NULL;
			//		}
		}

	}
	if(write_beg_i > 0)
	{
	for(k=0;k<write_beg_i;k++)
	{
		if(k==0)
		{
			qset=first;
		}
		else
		{
			qset=qset->next;	
		}
	}
	k--;
	quantum=(write_beg_qs+1)%noofreg;
	}
	else
	{
		qset=first;
		k=0;
		quantum=1;
	}
	for(i=k;i<noi;i++)
	{
		qset->data =(void**)kmalloc(sizeof(char *)*(noofreg),GFP_KERNEL);
		if(!qset->data)
		{
#ifdef DEBUG
			printk(KERN_ERR "qset->next ERROR\n");
#endif
			return (Qset *)-1;
		}
		memset(qset->data,'\0',sizeof(char *)*(noofreg));	
#ifdef DEBUG
		printk(KERN_INFO "write_beg_qs:%d\n",write_beg_qs);
#endif
		for(j=quantum-1;j<noofreg;j++)
		{
			qset->data[j] = (void*)kmalloc(sizeof(char)*(regsize-write_beg_q),GFP_KERNEL);
			noq--;
#ifdef DEBUG
	printk(KERN_INFO "noq:%d\n",noq);
#endif
			if(noq==0)
				break;
			memset(qset->data[j],'\0',sizeof(char)*regsize);	
		write_beg_q=0;
		}
		quantum=1;;
		qset=qset->next;
	}

#ifdef DEBUG
	printk(KERN_ALERT "Allocdev Ends\n");
#endif
	return first;
}
