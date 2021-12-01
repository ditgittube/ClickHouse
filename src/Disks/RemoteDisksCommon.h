#include <random>
#include <Core/Types.h>
#include <Common/thread_local_rng.h>
#include <Disks/DiskCacheWrapper.h>


namespace DB
{

String getRandomName(size_t len = 32, char first = 'a', char last = 'z');

std::shared_ptr<DiskCacheWrapper> wrapWithCache(
    std::shared_ptr<IDisk> disk, String cache_name, String cache_path, String metadata_path);

}
