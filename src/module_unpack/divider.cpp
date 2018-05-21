#include "divider.h"

//creates a string out_str from str1 and str2
void wcs2str(wchar_t *out_str, const wchar_t *str1, const wchar_t *str2)
{
	wcscpy_s(out_str, MAX_PATH, str1);
	wcscat_s(out_str, MAX_PATH - wcslen(out_str), str2);
}

// return 0 if the directory exists
uint8_t dir_exist(const wchar_t *path)
{
	struct _stat buf;
	if (_wstat(path, &buf) != 0)
	{
		return ERROR_NO_FOUND_PATH;
	}
	if (!(buf.st_mode & _S_IFDIR))
	{
		return ERROR_NOT_FOLDER;
	}
	return 0;
}

// return 0 if the file exists
uint8_t file_exist(const wchar_t *path)
{
	struct _stat buf;
	if (_wstat(path, &buf) != 0)
	{
		return ERROR_NO_FOUND_PATH;
	}
	if (buf.st_mode & _S_IFDIR)
	{
		return ERROR_NOT_FILE;
	}
	return 0;
}

_fsize_t file_size(const wchar_t *path)
{
	struct _stat buf;
	if (_wstat(path, &buf) != 0)
	{
		return 0;
	}
	return buf.st_size;
}

// create directories and subdirectories
uint8_t create_dir(const wchar_t *path)
{
	wchar_t cur_path[MAX_PATH] = { 0 };
	size_t len_path = wcslen(path);
	wcscpy_s(cur_path, path);
	wchar_t *ptr = cur_path;
	while ((wcslen(cur_path) > 0) && (_wmkdir(cur_path) != 0))
	{
		ptr = wcsrchr(cur_path, L'\\');
		if (ptr == NULL)
		{
			return ERROR_NOT_CREATE_DIR;
		}
		cur_path[ptr - cur_path] = L'\0';
	}
	if (wcslen(cur_path) == len_path)
	{
		return 0;
	}
	cur_path[ptr - cur_path] = L'\\';
	size_t len_cur_puth;
	while ((len_cur_puth = wcslen(cur_path)) <= len_path )
	{
		if (_wmkdir(cur_path) != 0)
		{
			return ERROR_NOT_CREATE_DIR;
		}
		cur_path[len_cur_puth] = L'\\';
	}
	return 0;
}


//if necessary, creates a subdirectory for the file
uint8_t creates_subdirectory(wchar_t fname[], const wchar_t out_path[])
{
	wchar_t *ptr = wcsrchr(fname, L'\\');
	if (ptr != nullptr)
	{
		wchar_t _path[MAX_PATH] = { 0 };
		wcs2str(_path, out_path, fname);
		_path[wcsrchr(_path, L'\\') - _path] = L'\0';
		if (dir_exist(_path) != 0)
		{
			uint8_t result = create_dir(_path);
			if (result != 0)
			{
				return result;
			}
		}
	}
	return 0;
}


// divide the merged file
uint8_t divide(const wchar_t* path, const wchar_t* filename)
{
	FILE *fin, *fout;
	if (_wfopen_s(&fin, filename, L"rb") != 0)
	{
		return ERROR_NOT_OPEN_FILE;
	}

	char* buf = (char*)malloc(SIZE_BUF);
	const _fsize_t size = file_size(filename);
	while ((feof(fin) == 0) && (_ftelli64(fin) < size))
	{
		wchar_t fname[MAX_PATH] = { 0 };
		for (uint16_t i = 0; (fname[i] = fgetwc(fin)) != L'\0'; ++i);

		if (creates_subdirectory(fname, path) != 0)
		{
			continue;
		}

		_fsize_t size_infile;
		fread(&size_infile, sizeof(_fsize_t), 1, fin);

		wchar_t full_fname[MAX_PATH] = { 0 };
		wcs2str(full_fname, path, fname);
		if (_wfopen_s(&fout, full_fname, L"wb") != 0)
		{
			continue;
		}

		for (_fsize_t read_b; size_infile > 0; size_infile -= read_b)
		{
			read_b = SIZE_BUF <= size_infile ? SIZE_BUF : size_infile;
			size_t num_b = fread(buf, 1, read_b, fin);
			if (num_b > 0)
			{
				fwrite(buf, 1, num_b, fout);
			}
		}
		fclose(fout);
	}
	fclose(fin);
	free(buf);
	return 0;
}


uint8_t before_divide(const wchar_t* path, const wchar_t* filename)
{
	uint8_t result;
	if ((result = file_exist(filename)) == 0)
	{
		if ((dir_exist(path) == 0) || ((result = create_dir(path)) == 0))
		{
			result = divide(path, filename);
		}
	}
	return result;
}
