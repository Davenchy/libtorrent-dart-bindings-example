import 'dart:ffi';
import 'package:ffi/ffi.dart';
import 'storage.dart';
import 'native.dart';
import 'extensions.dart';

export 'storage.dart';


Storage getStorage(String magnetUri) {
  // allocate a new cstring
  final Pointer<Utf8> magnetUriPtr = magnetUri.toNativeUtf8();

  // Call the C function and pass the allocated cstring
  // then get the storage object pointer
  final Pointer<StorageStruct> storagePtr = storageGetC(magnetUriPtr);

  // free the allocated string
  malloc.free(magnetUriPtr);

  // create dart storage object from the native one
  final Storage storage =  storagePtr.toStorage();

  // free the native storage
  storageFreeC(storagePtr);

  return storage;
}
