#pragma once

#include "manifest.h"
#include "path.h"

class StringList;
class StringListKV;
struct Timestamp;

struct BuildOptions
{
    ::helpers::path output_dir;
    ::helpers::path build_script_overrides;
    ::std::vector<::helpers::path>  lib_search_dirs;
    const char* target_name = nullptr;	// if null, host is used
};

class BuildList
{
    struct Entry
    {
        const PackageManifest*  package;
	bool	is_host;
        ::std::vector<unsigned> dependents;   // Indexes into the list
    };
    const PackageManifest&  m_root_manifest;
    // List is sorted by build order
    ::std::vector<Entry>    m_list;
public:
    BuildList(const PackageManifest& manifest, const BuildOptions& opts);
    bool build(BuildOptions opts, unsigned num_jobs);  // 0 = 1 job
};
