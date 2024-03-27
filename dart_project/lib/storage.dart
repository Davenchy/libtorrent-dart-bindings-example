final class StorageFile {
  final String name;
  final String path;
  final int size;

  const StorageFile(this.name, this.path, this.size);
}

final class Storage {
  final List<StorageFile> files;
  final int totalSize;

  const Storage(this.files, this.totalSize);
}
