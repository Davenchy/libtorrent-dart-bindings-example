import 'dart:ffi';
import 'package:ffi/ffi.dart';


// Define the structure representing file_t
// Order of members is very important, it should be the same as the definiation
// in the .hpp file
final class FileStruct extends Struct {
  @Int64()
  external int size;
  external Pointer<Utf8> name;
  external Pointer<Utf8> path;
}

// Define the structure representing storage_t
final class StorageStruct extends Struct {
  @Int64()
  external int count;
  @Int64()
  external int size;
  external Pointer<FileStruct> files;
}

// Define the function signature
typedef StorageGetC = Pointer<StorageStruct> Function(Pointer<Utf8>);
typedef StorageFreeC = Void Function(Pointer<StorageStruct>);
typedef StorageFreeFunc = void Function(Pointer<StorageStruct>);

// Load the shared library
final DynamicLibrary myLibrary = DynamicLibrary.open('./libwrapper.so');

// Load the C function
final StorageGetC storageGetC = myLibrary
    .lookupFunction<StorageGetC, StorageGetC>('storage_get');

final StorageFreeFunc storageFreeC = myLibrary
    .lookupFunction<StorageFreeC, StorageFreeFunc>('storage_free');
