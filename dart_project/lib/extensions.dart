import 'dart:ffi';
import 'package:ffi/ffi.dart';
import 'storage.dart';
import 'native.dart';


extension StoragePointerToStorage on Pointer<StorageStruct> {
  Storage toStorage() {
    final files = List<StorageFile>.generate(ref.count, (int index) {
      final FileStruct file = ref.files[index];
      return StorageFile(
        file.name.toDartString(),
        file.path.toDartString(),
        file.size,
      );
    });

    return Storage(files, ref.size);
  }
}
