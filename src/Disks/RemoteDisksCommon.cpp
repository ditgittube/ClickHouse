#include <Disks/RemoteDisksCommon.h>

namespace DB
{

namespace ErrorCodes
{
    extern const int BAD_ARGUMENTS;
}


String getRandomName(size_t len, char first, char last)
{
    std::uniform_int_distribution<int> distribution(first, last);
    String res(len, ' ');
    for (auto & c : res)
        c = distribution(thread_local_rng);
    return res;
}


std::shared_ptr<DiskCacheWrapper> wrapWithCache(
    std::shared_ptr<IDisk> disk, String cache_name, String cache_path, String metadata_path)
{
    if (metadata_path == cache_path)
        throw Exception("Metadata and cache paths should be different: " + metadata_path, ErrorCodes::BAD_ARGUMENTS);

    auto cache_disk = std::make_shared<DiskLocal>(cache_name, cache_path, 0);
    auto cache_file_predicate = [] (const String & path)
    {
        return path.ends_with("idx") // index files.
                || path.ends_with("mrk") || path.ends_with("mrk2") || path.ends_with("mrk3") /// mark files.
                || path.ends_with("txt") || path.ends_with("dat");
    };

    return std::make_shared<DiskCacheWrapper>(disk, cache_disk, cache_file_predicate);
}

}
