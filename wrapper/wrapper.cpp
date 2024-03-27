#include <libtorrent/session.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/alert.hpp>
#include <libtorrent/alert_types.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "wrapper.hpp"

#define MAGNET_URI "magnet:?xt=urn:btih:08ada5a7a6183aae1e09d831df6748d566095a10&dn=Sintel&tr=udp%3A%2F%2Fexplodie.org%3A6969&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.empire-js.us%3A1337&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Ftracker.opentrackr.org%3A1337&tr=wss%3A%2F%2Ftracker.btorrent.xyz&tr=wss%3A%2F%2Ftracker.fastcast.nz&tr=wss%3A%2F%2Ftracker.openwebtorrent.com&ws=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2F&xs=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2Fsintel.torrent"

/**
 * This function will download the torrent_metadata from peers and returns it
 * back
 */
std::shared_ptr<const lt::torrent_info>
download_torrent_info(const char *magnet_uri) {
  // initialize session settings pack to let the session emits status alerts
  lt::settings_pack pack;
  pack.set_int(lt::settings_pack::alert_mask,lt::alert_category::status);

  // create a new session with the settings_pack
  lt::session ses {pack};

  // define the torrent parameters using the maagent uri
  lt::add_torrent_params params = lt::parse_magnet_uri(magnet_uri);
  // set this torrent to be in upload mode only, so no files will be downloaded
  params.flags |= lt::torrent_flags::upload_mode;

  // add the torrent parameters to the session and get its handler
  lt::torrent_handle handle = ses.add_torrent(params);

  // loop through each alert
  while(true) {
    std::vector<lt::alert*> alerts;
    ses.pop_alerts(&alerts);

    for (auto const* alert : alerts) {
      // if received the metadata_received alert then return the torrent info
      if (lt::alert_cast<lt::metadata_received_alert>(alert))
        return handle.torrent_file();
    }
  }

  return nullptr;
}

const storage_t *storage_get(const char *magnet_uri) {
  // request the torrent file info from manget uri using libtorrent
  const auto info = download_torrent_info(magnet_uri);

  if (info == nullptr) return nullptr;
  const int count = info->num_files(); // get the files count

  // allocate memory of the size of ``storage_t``
  // and a ``file_t`` for each file
  storage_t *const storage = (storage_t *)malloc(
      sizeof(storage_t) + (sizeof(file_t) * count));

  if (storage == nullptr) return nullptr;
  // set the files pointer to start after the storage object
  // in the allocated memory
  storage->files = (file_t *)(storage + 1);
  storage->count = count;

  // get the files from libtorrent::storage object
  const auto t_storage = info->files();
  // get the files range to loop for each file index
  const auto range = t_storage.file_range();
  // get the total torrent size
  storage->size = t_storage.total_size();

  try {
    for (auto const& i /* index */ : range) {
      // get reference to a file object
      file_t& file = storage->files[i];

      // set the size
      file.size = t_storage.file_size(i);

      // allocate and copy the file path from ``boost::string``
      // as the storage object will be out of the memory
      // at the end of this function scope
      file.path = strdup(t_storage.file_path(i).c_str());
      if (file.path == nullptr) goto fail;

      // do the same for the ``filename`` but this time ``file_name`` returns
      // ``boost::string_view``
      const auto name = t_storage.file_name(i);
      file.name = strndup(name.data(), name.size());
      if (file.name == nullptr) {
        free((void *)file.path);
        goto fail;
      }
    }
  } catch (std::exception e) {
    goto fail;
  }

  return storage;
fail:
  // on fail, free the allocated memory and return NULL
  storage_free(storage);
  return nullptr;
}

void storage_free(const storage_t *storage) {
  if (!storage) return;

  for (int i = 0; i < storage->count; i++) {
    const file_t& file = storage->files[i];

    if (file.name) free((void *)file.name);
    if (file.path) free((void *)file.path);
  }

  free((void *)storage);
}

int main() {
  const storage_t *storage = storage_get(MAGNET_URI);

  if (!storage) {
    std::cerr << "Failed to get storage!\n";
    return 1;
  }

  std::cout << "Size: " << storage->size << '\n';
  for (int i = 0; i < storage->count; i++) {
    const auto file = storage->files[i];
    std::cout << "Name: " << file.name << '\n';
    std::cout << "Path: " << file.path << '\n';
    std::cout << "Size: " << file.size << '\n';
    std::cout << '\n';
  }

  storage_free(storage);
}
