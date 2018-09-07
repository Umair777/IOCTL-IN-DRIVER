struct file_operations fops =
{
	open : Opendev,
	write: Writedev,
	read: Readdev,
	llseek: Seekdev,
	release: Releasedev,
	unlocked_ioctl:ioctl_dev
};
