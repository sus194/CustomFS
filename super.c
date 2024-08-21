#include <linux/fs.h>
#include "myfs.h"

static int myfs_fill_super(struct super_block *sb, void *data, int silent) {
    struct inode *root_inode;

    sb->s_magic = MYFS_MAGIC_NUMBER; // Custom file system magic number
    sb->s_op = &myfs_super_ops;      // Pointer to your superblock operations

    root_inode = myfs_make_inode(sb, S_IFDIR | 0755); // Create root inode
    if (!root_inode)
        return -ENOMEM;

    sb->s_root = d_make_root(root_inode); // Set the root dentry
    if (!sb->s_root)
        return -ENOMEM;

    return 0;
}

static struct dentry *myfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data) {
    return mount_bdev(fs_type, flags, dev_name, data, myfs_fill_super);
}

static void myfs_kill_superblock(struct super_block *sb) {
    kill_block_super(sb);
}

static struct file_system_type myfs_fs_type = {
    .owner = THIS_MODULE,
    .name = "myfs",
    .mount = myfs_mount,
    .kill_sb = myfs_kill_superblock,
    .fs_flags = FS_REQUIRES_DEV,
};

static int __init myfs_init(void) {
    return register_filesystem(&myfs_fs_type);
}

static void __exit myfs_exit(void) {
    unregister_filesystem(&myfs_fs_type);
}

module_init(myfs_init);
module_exit(myfs_exit);
MODULE_LICENSE("GPL");
