#include <linux/fs.h>
#include <linux/uaccess.h>
#include "myfs.h"

static ssize_t myfs_read(struct file *filp, char __user *buf, size_t len, loff_t *offset) {
    struct inode *inode = filp->f_inode;
    struct myfs_inode *my_inode = MYFS_INODE(inode); // Custom inode structure
    char *data = my_inode->data; // Pointer to file data

    if (*offset >= my_inode->size)
        return 0; // End of file

    if (*offset + len > my_inode->size)
        len = my_inode->size - *offset; // Adjust read length

    if (copy_to_user(buf, data + *offset, len))
        return -EFAULT; // Error copying data to user space

    *offset += len; // Update file offset
    return len;
}

static struct file_operations myfs_file_ops = {
    .read = myfs_read,
    // Other file operations can be defined here (e.g., write, open, etc.)
};
