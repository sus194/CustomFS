struct inode *myfs_make_inode(struct super_block *sb, int mode) {
    struct inode *inode = new_inode(sb);
    if (inode) {
        inode->i_mode = mode;
        inode->i_uid = current_fsuid();
        inode->i_gid = current_fsgid();
        inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
    }
    return inode;
}