#include <linux/fs.h>
#include "myfs.h"

static struct inode *myfs_make_inode(struct super_block *sb, umode_t mode) {
    struct inode *inode = new_inode(sb);
    if (inode) {
        inode->i_mode = mode;
        inode->i_uid = current_fsuid();
        inode->i_gid = current_fsgid();
        inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
    }
    return inode;
}

static int myfs_create(struct inode *dir, struct dentry *dentry, umode_t mode, bool excl) {
    struct inode *inode = myfs_make_inode(dir->i_sb, mode);
    if (!inode)
        return -ENOSPC;

    inode->i_op = &myfs_inode_ops; // Set inode operations
    inode->i_fop = &myfs_file_ops; // Set file operations

    d_instantiate(dentry, inode); // Link dentry with the new inode
    return 0;
}

static struct inode_operations myfs_inode_ops = {
    .create = myfs_create,
    // Other inode operations can be defined here (e.g., lookup, unlink, etc.)
};
