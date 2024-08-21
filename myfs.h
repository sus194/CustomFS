#ifndef _MYFS_H
#define _MYFS_H

#include <linux/fs.h>  // For struct super_block, struct inode, struct file, etc.
#include <linux/pagemap.h> // For simple file system helpers

#define MYFS_MAGIC_NUMBER 0x13131313  // Unique magic number for your file system

// Custom inode structure (if you have additional metadata)
struct myfs_inode {
    struct inode vfs_inode;  // Embed the VFS inode structure
    char *data;              // Pointer to file data (simple example)
    size_t size;             // Size of the file
};

// Macros for easier access to custom inode structure
#define MYFS_INODE(inode) container_of(inode, struct myfs_inode, vfs_inode)

// Function prototypes

// Superblock operations
int myfs_fill_super(struct super_block *sb, void *data, int silent);

// Inode operations
struct inode *myfs_make_inode(struct super_block *sb, umode_t mode);
int myfs_create(struct inode *dir, struct dentry *dentry, umode_t mode, bool excl);

// File operations
ssize_t myfs_read(struct file *filp, char __user *buf, size_t len, loff_t *offset);

#endif  /* _MYFS_H */
