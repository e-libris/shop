#ifndef GETRESOURCES_H
#define GETRESOURCES_H

#include <stdio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

static size_t write_data(void*, size_t, size_t, void*);
void download(vector<string>&);
void get_resources();

#endif /* GETRESOURCES_H */
