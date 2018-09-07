#ifndef MAGIC 
#define MAGIC 't'
#endif

#ifndef GETREGSIZE
#define GETREGSIZE _IOW(MAGIC,0,int)
#endif

#ifndef GETNOOFREG
#define GETNOOFREG _IOW(MAGIC,1,int)
#endif

#ifndef GETDEVICESIZE
#define GETDEVICESIZE _IOW(MAGIC,2,int)
#endif

#ifndef GETDATASIZE
#define GETDATASIZE _IOW(MAGIC,3,int)
#endif

#ifndef SETREGSIZE
#define SETREGSIZE _IOR(MAGIC,4,int)
#endif

#ifndef SETNOOFREG
#define SETNOOFREG _IOW(MAGIC,5,int)
#endif

#ifndef DEVRESET
#define DEVRESET _IO(MAGIC,9)
#endif
