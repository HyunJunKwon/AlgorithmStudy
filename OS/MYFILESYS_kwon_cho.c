/*----------------------------------------------------------------------------------------------------------------------------------
O.S PROJECT-3
FILE IMPLEMENTATION USING FUSE
FINAL CREATION: 2016-12-12
권현준
조영도
------------------------------------------------------------------------------------------------------------------------------------*/
// Define constants
#define MAX 512
#define FUSE_USE_VERSION 26

// Header files inclusion
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fuse.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>

// Define struct
typedef struct _MYFILESYS
{
	int type;  // Variable to assign type, 0 is file and 1 is directory
	char name[MAX]; // Name of file or directory
	long size; // Variable to assign file size
	char * data; // Variable to assign file data
	int lowerNum; // Number of lower
	mode_t mode; // Mode of file (permission)
	uid_t uid; // User id of file
	gid_t gid; // Group id of file
	time_t a_time;// Variable to notify access time
	time_t c_time; // Variable to notify changing time           
	time_t m_time;// Variable to notify modification time
	struct _MYFILESYS * upper; // Upper directory, because upper directory is one
	struct _MYFILESYS ** lower;  // Lower directory, because lower directory is many
}MYFILESYS;

// Define enum
typedef enum
{
	FILE1,
	DIRECTORY
}TYPE;

// Global variables declare
MYFILESYS * root; // root declare

				  // Functions declare
const char * Set_Path_Prev(const char * path);
MYFILESYS * Get_Info(const char * path, int type);
const char * get_Name_of_Path(const char * path);

// Functions definition
static int MYFILESYS_getattr(const char * path, struct stat * stbuf)
{
	/*
	Return file attributes.
	For the given pathname, this should fill in the elements of the "stat" structure.
	If a field is meaningless or semi-meaningless (e.g., st_ino) then it should be set to 0 or given a "reasonable" value.
	This call is pretty much required for a usable filesystem.
	*/

	// Local variables declare
	MYFILESYS * temp = NULL;

	// Statements
	memset(stbuf, 0, sizeof(struct stat)); // Set stbuf to 0

	temp = Get_Info(path, DIRECTORY); // Get information about directory to temp variable
	if (temp != NULL) // If temp is not null value, assing information to stbuf
	{
		stbuf->st_mode = temp->mode;
		stbuf->st_atime = temp->a_time;
		stbuf->st_mtime = temp->m_time;
		stbuf->st_uid = temp->uid;
		stbuf->st_gid = temp->gid;
		return 0;
	}

	temp = Get_Info(path, FILE1); // Get information about file to temp variable
	if (temp != NULL)
	{
		stbuf->st_mode = temp->mode;
		stbuf->st_size = temp->size;
		stbuf->st_atime = temp->a_time;
		stbuf->st_mtime = temp->m_time;
		stbuf->st_uid = temp->uid;
		stbuf->st_gid = temp->gid;
		return 0;
	}
	return -ENOENT;
}
static int MYFILESYS_readdir(const char * path, void * buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info * fi)
{
	/*
	The readdir function is somewhat like read, in that it starts at a given offset and returns results in a caller-supplied buffer.
	However, the offset not a byte offset, and the results are a series of struct dirents rather than being uninterpreted bytes.
	*/
	// Local variables declare
	MYFILESYS * temp = NULL;
	MYFILESYS * temp2 = NULL;
	int i = 0;

	// Statements
	temp = Get_Info(path, DIRECTORY); // Get information about directory to temp variable
	if (temp == NULL)
		return -ENOENT; // No such file or directory
	if (!(temp->mode & S_IRUSR)) // If directory mode is not a S_IRUSR(00400, Read permission to user)
		return -EACCES; // Permission denied

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0); // Call the filler function with arguments of buf, the null-terminated filename, 
								//the address of your struct stat (or NULL if you have none), and the offset of the next directory entry.
								//If filler returns nonzero, or if there are no more files, return 0.

	if (temp->lower == NULL)
		return 0;
	else
	{
		for (i = 0; i < temp->lowerNum; i++)
		{
			temp2 = temp->lower[i];
			filler(buf, temp2->name, NULL, 0); // Read directory
		}
	}
	return 0;
}
static int MYFILESYS_mkdir(const char * path, mode_t mode)
{
	/*
	Create a directory with the given name.
	The directory permissions are encoded in mode.
	This function is needed for any reasonable read/write filesystem.
	*/

	// Local variables declare
	MYFILESYS * temp = NULL;
	char * temp2 = NULL;
	char * base = NULL;
	char * temp_path = NULL;
	int i = 0;
	int loop = 1;

	// Statements
	temp_path = (char *)malloc(sizeof(char) * MAX);
	temp = Get_Info(path, DIRECTORY); // Get information about directory to temp variable

	if (temp != NULL)
		return -EEXIST;

	strcpy(temp_path, path);
	base = strtok(temp_path, "/");
	while (loop)
	{
		temp2 = strtok(NULL, "/");
		if (temp2 == NULL)
			break;
		else strcpy(base, temp2);
	}

	temp = Get_Info(Set_Path_Prev(path), DIRECTORY);
	if (temp == NULL)
		return -EACCES;
	if (temp->lower == NULL)
	{
		temp->lower = (MYFILESYS **)malloc(sizeof(MYFILESYS *));
		temp->lower[0] = (MYFILESYS *)malloc(sizeof(MYFILESYS));
		strcpy(temp->lower[0]->name, base);
		temp->lower[0]->mode = S_IFDIR | mode;
		temp->lower[0]->uid = getuid();
		temp->lower[0]->gid = getgid();
		temp->lower[0]->upper = temp;
		temp->lower[0]->lower = NULL;
		temp->lower[0]->size = 0;
		temp->lower[0]->data = NULL;
		temp->lower[0]->lowerNum = 0;
		temp->lowerNum = 1;
		temp->lower[0]->type = DIRECTORY;
	}
	else
	{
		i = temp->lowerNum;
		temp->lower = (MYFILESYS **)realloc(temp->lower, sizeof(MYFILESYS*)*(i + 1));
		temp->lower[i] = (MYFILESYS *)malloc(sizeof(MYFILESYS));
		strcpy(temp->lower[i]->name, base);
		temp->lower[i]->mode = S_IFDIR | mode;
		temp->lower[i]->uid = getuid();
		temp->lower[i]->gid = getgid();
		temp->lower[i]->upper = temp;
		temp->lower[i]->lower = NULL;
		temp->lower[i]->size = 0;
		temp->lower[i]->data = NULL;
		temp->lower[i]->lowerNum = 0;
		temp->lowerNum++;
		temp->lower[i]->type = DIRECTORY;
	}

	return 0;
}
static int MYFILESYS_rmdir(const char * path)
{
	/*
	Remove the given directory.
	This should succeed only if the directory is empty (except for "." and "..")
	*/

	// Local variables declare
	MYFILESYS * temp = NULL;
	MYFILESYS * upper = NULL;
	int i = 0;
	int j = 0;

	// Statements
	temp = Get_Info(path, DIRECTORY); // Get information about directory to temp variable
	if (temp == NULL)
		return -EACCES; // Permission denied
	if (temp->lowerNum != 0) // If there is at least one lower files,
		return -ENOTEMPTY;


	//From the parent of it, Search one by one, delete it, and rearrange children of the parent
	upper = temp->upper; // Assign temp->upper to upper because we will modify data structure
	for (i = 0; i < upper->lowerNum; i++)
	{
		if (upper->lower[i] == temp)
		{
			for (j = i; j < upper->lowerNum - 1; j++)
				upper->lower[j] = upper->lower[j + 1];
			if (upper->lowerNum == 1)
			{
				free(upper->lower);
				upper->lower = NULL;
			}
			else
				upper->lower = (MYFILESYS **)realloc(upper->lower, sizeof(MYFILESYS*)*(upper->lowerNum - 1));
			free(temp);
			upper->lowerNum--;
			// Modify linked list
		}
	}
	return 0;
}
static int MYFILESYS_mknod(const char * path, mode_t mode, dev_t dev)
{
	/*
	Make a special (device) file, FIFO, or socket.
	This function is rarely needed,
	since it's uncommon to make these objects inside special-purpose filesystems.
	*/

	// Local variables declare
	MYFILESYS * temp = NULL;
	char * lower = NULL;
	char * temp2 = NULL;
	char t_path[MAX] = { 0, };
	int i = 0;
	int loop = 1;

	// Statements
	temp = Get_Info(path, FILE1);

	if (temp != NULL)
		return -EEXIST;
	else
	{

		temp = Get_Info(Set_Path_Prev(path), DIRECTORY);
		if (temp == NULL)
			return -ENOENT; // No such file or directory

							//Search the name of the file in the variable 'path'
		strcpy(t_path, path);
		lower = strtok(t_path, "/");
		while (loop)
		{
			temp2 = strtok(NULL, "/");
			if (temp2 == NULL)
				break;
			else strcpy(lower, temp2);
		}
		if (temp->lower == NULL)
		{

			temp->lower = (MYFILESYS**)malloc(sizeof(MYFILESYS*));
			temp->lower[0] = (MYFILESYS*)malloc(sizeof(MYFILESYS));
			strcpy(temp->lower[0]->name, lower);
			temp->lower[0]->mode = mode;
			temp->lower[0]->uid = getuid();
			temp->lower[0]->gid = getgid();
			temp->lower[0]->upper = temp;
			temp->lower[0]->lower = NULL;
			temp->lower[0]->size = 0;
			temp->lower[0]->data = NULL;
			temp->lower[0]->lowerNum = 0;
			temp->lowerNum = 1;
			temp->lower[0]->type = FILE1;
		}
		else
		{
			i = temp->lowerNum;
			temp->lower = (MYFILESYS**)realloc(temp->lower, sizeof(MYFILESYS *) * (i + 1));
			temp->lower[i] = (MYFILESYS*)malloc(sizeof(MYFILESYS));
			strcpy(temp->lower[i]->name, lower);
			temp->lower[i]->mode = mode;
			temp->lower[i]->uid = getuid();
			temp->lower[i]->gid = getgid();
			temp->lower[i]->upper = temp;
			temp->lower[i]->lower = NULL;
			temp->lower[i]->size = 0;
			temp->lower[i]->data = NULL;
			temp->lower[i]->lowerNum = 0;
			temp->lowerNum++;
			temp->lower[i]->type = FILE1;
		}
	}

	return 0;
}
static int MYFILESYS_read(const char * path, char * buf, size_t size, off_t offset, struct fuse_file_info * fi)
{
	// Local variables declare
	MYFILESYS * temp = NULL;
	int mode = 0;

	// Statements
	(void)fi;
	temp = Get_Info(path, FILE1); // Get information about file to temp variable
	mode = fi->flags & 3; // Open flags. (O_RDONLY)

	if (temp == NULL)
		return -ENOENT; // If there is no file
	if (temp->data == NULL)
		return 0;
	if (offset + size > temp->size) {
		memcpy(buf, temp->data + offset, temp->size - offset);
		return temp->size - offset;
	}
	memcpy(buf, temp->data + offset, size);
	return size;
}
static int MYFILESYS_utimens(const char * path, const struct timespec ts[2])
{
	// Local variables declare
	MYFILESYS * temp = NULL;

	// Statements
	temp = Get_Info(path, FILE1); // Get information about file to temp variable
	temp->a_time = ts[0].tv_sec;
	temp->m_time = ts[1].tv_sec;// Update the last access time of the given object from ts[0] 
								//and the last modification time from ts[1].
	return 0;
}
static int MYFILESYS_open(const char * path, struct fuse_file_info * fi)
{
	/*
	Open a file. If you aren't using file handles,
	this function should just check for existence and permissions
	and return either success or an error code.
	If you use file handles, you should also allocate any necessary structures and set fi->fh.
	*/

	// Local variable decalre
	MYFILESYS * temp = NULL;

	// Statements
	temp = Get_Info(path, FILE1); // Get information about file to temp variable
	if (temp == NULL)
		return -ENOENT;
	return 0;
}
static int MYFILESYS_write(const char * path, const char * buf, size_t size, off_t offset, struct fuse_file_info * fi)
{
	// As for 'MYFILESYS_read' function above, except that it can't return 0.

	// Local variables declare
	MYFILESYS * temp = NULL;
	int len = 0;

	// Statements
	temp = Get_Info(path, FILE1); // Get information about file to temp variable
	len = temp->size - (offset + size);

	if (temp == NULL)
		return -ENOENT;

	if (temp->data == NULL)
	{
		temp->size = size;
		temp->data = (char *)malloc(size);
		memcpy(temp->data, buf, size);
		return size;
	}

	if (offset + size > temp->size) {
		temp->size -= offset;
		temp->data = (char *)realloc(temp->data, temp->size);
		memcpy(temp->data + offset, buf, temp->size);
		return temp->size;
	}
	temp->size = size;
	temp->data = (char *)realloc(temp->data, temp->size);
	memcpy(temp->data + offset, buf, temp->size);
	return size;
}
static int MYFILESYS_unlink(const char * path)
{
	/*
	Remove (delete) the given file, symbolic link, hard link, or special node.
	Note that if you support hard links, unlink only deletes the data when the last hard link is removed.
	*/

	// Local variables declare
	MYFILESYS * upper_info = NULL;
	MYFILESYS * file_info = NULL;
	int i = 0;
	int j = 0;

	// Statements
	upper_info = Get_Info(Set_Path_Prev(path), DIRECTORY); // Get information about directory to temp variable
	file_info = Get_Info(path, FILE1); // Get information about file to temp variable

	if (file_info == NULL)
		return -EACCES;
	// Modify linked list
	// Using prev path, modify linked list
	for (i = 0; i < upper_info->lowerNum; i++)
	{
		if (upper_info->lower[i] == file_info)
		{
			for (j = i; j < upper_info->lowerNum - 1; j++)
			{
				upper_info->lower[j] = upper_info->lower[j + 1];
			}
			if (upper_info->lowerNum == 1)
			{
				free(upper_info->lower);
				upper_info->lower = NULL;
			}
			else
			{
				upper_info->lower = (MYFILESYS **)realloc(upper_info->lower, sizeof(MYFILESYS *) * (upper_info->lowerNum - 1));
			}
			free(file_info);
			upper_info->lowerNum--;
		}
	}
	return 0;
}

static int MYFILESYS_chmod(const char * path, mode_t mode)
{
	/*
	Change the permission of a file or directory
	*/

	// Local variables declare
	MYFILESYS * file_info;

	// Statements
	file_info = Get_Info(path, FILE1);

	if (file_info == NULL)
		return -ENOENT;
	else
		file_info->mode = mode;
	return 0;
}


static int MYFILESYS_chown(const char * path, uid_t uid, gid_t gid)
{
	/*
	Change the owner of a file or directory
	*/
	// Local variables declare
	MYFILESYS * file_info;

	// Statements
	file_info = Get_Info(path, FILE1);

	if (file_info == NULL)
		return -ENOENT;
	else {
		file_info->uid = uid;
		file_info->gid = gid;
	}
	return 0;
}

static int MYFILESYS_rename(const char *from, const char *to)
{
	/*
	Change the owner of a file or directory
	*/
	// Local variables declare
	MYFILESYS * file_info_from;
	MYFILESYS * file_info_to;

	// Statements
	file_info_from = Get_Info(from, FILE1);
	if (file_info_from == NULL) {
		//type of 'from' is directory, so 'to' also directory  
		file_info_from = Get_Info(from, DIRECTORY);
		file_info_to = Get_Info(to, DIRECTORY);
		if (file_info_from != NULL && file_info_to == NULL) {
			strcpy(file_info_from->name, get_Name_of_Path(to));
		}
		else {
			return -ENOENT;
		}
	}
	else { //type of 'from' is file, so 'to' also file  
		file_info_to = Get_Info(to, FILE1);
		if (file_info_to == NULL) {
			strcpy(file_info_from->name, get_Name_of_Path(to));
		}
		else {
			return -ENOENT;
		}
	}
	return 0;
}

void Set_root()
{
	/*
	Setting root to drwxr-xr-x
	*/
	// Statements
	root = (MYFILESYS *)malloc(sizeof(MYFILESYS));
	strcpy(root->name, "ROOT");
	root->mode = S_IFDIR | 0755; // Set root's mode to 0755(rwxr-xr-x) which means 
								 // the owner has read, write and execute permissions,
								 //the group and others can only read and execute
	root->uid = getuid(); // Get user id 
	root->gid = getgid(); // Get group id
	root->data = NULL;
	root->upper = NULL;
	root->lower = NULL;
	root->size = 0;
	root->lowerNum = 0;
	root->type = DIRECTORY; // Set data type to 'directory'
}
static struct fuse_operations MYFILESYS_OPER =
{
	.getattr = MYFILESYS_getattr,
	.readdir = MYFILESYS_readdir,
	.mkdir = MYFILESYS_mkdir,
	.rmdir = MYFILESYS_rmdir,
	.mknod = MYFILESYS_mknod,
	.read = MYFILESYS_read,
	.utimens = MYFILESYS_utimens, // To get change, access, modification times of a file
	.open = MYFILESYS_open,
	.write = MYFILESYS_write,
	.unlink = MYFILESYS_unlink,
	.chmod = MYFILESYS_chmod,
	.chown = MYFILESYS_chown,
	.rename = MYFILESYS_rename,
};

int main(int argc, char *argv[])
{
	// Statements
	Set_root();
	return fuse_main(argc, argv, &MYFILESYS_OPER, NULL);
}
const char * get_Name_of_Path(const char * path) {
	char * name = (char *)malloc(sizeof(char) * MAX);
	int i, j, len = strlen(path);
	for (i = len - 1; i >= 0; i--)
	{
		if (path[i] == '/')
			break;
	}
	for (j = i + 1; j < len; j++)
	{
		name[j - (i + 1)] = path[j];
	}
	return name;
}
// Functions definition
const char * Set_Path_Prev(const char * path)
{
	/*
	Set path to prev [ex: /a/b/c -> /a/b] to use modify linked list
	*/
	// Local variables declare
	char * prev_path = NULL;
	int i = 0;
	int len = 0;
	// Statements
	prev_path = (char *)malloc(sizeof(char) * MAX);
	len = strlen(path);
	for (i = len - 1; i >= 0; i--)
	{
		if (path[i] == '/')
			break;
	}
	strncpy(prev_path, path, i);
	prev_path[i] = '\0';
	return prev_path;
}

MYFILESYS * Get_Info(const char * path, int type) // Get file or directory information 
{
	// Local variables declare
	MYFILESYS * temp_root = NULL;
	MYFILESYS * temp2 = NULL;
	char temp_path[MAX] = { 0, };
	char * base = NULL; // Variable base, it will be assigned to home directory value
	int i = 0;
	int loop = 1;
	// Statements
	temp_root = root; // Assign root information to temp variable
	strcpy(temp_path, path); // Assign path information to temp variable
	base = strtok(temp_path, "/"); // This function returns a pointer to the last token found in the string.
								   // a null pointer is returned if there are no tokens left to retrieve.
	if (base == NULL) // If path is NULL (Initial state)
	{
		if (type == DIRECTORY) // If type is directory
			return root;
		else
			return NULL;
	}
	while (loop)
	{
		if (temp_root->lower != NULL) // If root has lower struct, 
		{
			for (i = 0; i < temp_root->lowerNum; i++)
			{
				temp2 = temp_root->lower[i];
				if (!strcmp(temp2->name, base)) // If temp2->name is same base struct's name,
				{
					base = strtok(NULL, "/");
					if (base == NULL)
					{
						if (temp2->type == type)
							return temp2;
						else
							return NULL;
					}
					else
					{
						temp_root = temp2;
						break;
					}
				}
			}
			if (temp_root != temp2)
				return NULL;
		}
		else
			return NULL;
	}
}