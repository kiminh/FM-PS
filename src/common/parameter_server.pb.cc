// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: parameter_server.proto

#include "parameter_server.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_parameter_5fserver_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_KeyValuePair_parameter_5fserver_2eproto;
namespace task {
class ParametersOrGradientsDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ParametersOrGradients> _instance;
} _ParametersOrGradients_default_instance_;
class KeyValuePairDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<KeyValuePair> _instance;
} _KeyValuePair_default_instance_;
}  // namespace task
static void InitDefaultsscc_info_KeyValuePair_parameter_5fserver_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::task::_KeyValuePair_default_instance_;
    new (ptr) ::task::KeyValuePair();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::task::KeyValuePair::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_KeyValuePair_parameter_5fserver_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_KeyValuePair_parameter_5fserver_2eproto}, {}};

static void InitDefaultsscc_info_ParametersOrGradients_parameter_5fserver_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::task::_ParametersOrGradients_default_instance_;
    new (ptr) ::task::ParametersOrGradients();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::task::ParametersOrGradients::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_ParametersOrGradients_parameter_5fserver_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_ParametersOrGradients_parameter_5fserver_2eproto}, {
      &scc_info_KeyValuePair_parameter_5fserver_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_parameter_5fserver_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_parameter_5fserver_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_parameter_5fserver_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_parameter_5fserver_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::task::ParametersOrGradients, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::task::ParametersOrGradients, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::task::ParametersOrGradients, pairs_),
  ~0u,
  PROTOBUF_FIELD_OFFSET(::task::KeyValuePair, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::task::KeyValuePair, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::task::KeyValuePair, name_),
  PROTOBUF_FIELD_OFFSET(::task::KeyValuePair, dim_),
  PROTOBUF_FIELD_OFFSET(::task::KeyValuePair, shape_),
  PROTOBUF_FIELD_OFFSET(::task::KeyValuePair, values_),
  0,
  1,
  ~0u,
  ~0u,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 6, sizeof(::task::ParametersOrGradients)},
  { 7, 16, sizeof(::task::KeyValuePair)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::task::_ParametersOrGradients_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::task::_KeyValuePair_default_instance_),
};

const char descriptor_table_protodef_parameter_5fserver_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026parameter_server.proto\022\004task\":\n\025Parame"
  "tersOrGradients\022!\n\005pairs\030\001 \003(\0132\022.task.Ke"
  "yValuePair\"H\n\014KeyValuePair\022\014\n\004name\030\001 \001(\t"
  "\022\013\n\003dim\030\002 \001(\r\022\r\n\005shape\030\003 \003(\r\022\016\n\006values\030\004"
  " \003(\002"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_parameter_5fserver_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_parameter_5fserver_2eproto_sccs[2] = {
  &scc_info_KeyValuePair_parameter_5fserver_2eproto.base,
  &scc_info_ParametersOrGradients_parameter_5fserver_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_parameter_5fserver_2eproto_once;
static bool descriptor_table_parameter_5fserver_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_parameter_5fserver_2eproto = {
  &descriptor_table_parameter_5fserver_2eproto_initialized, descriptor_table_protodef_parameter_5fserver_2eproto, "parameter_server.proto", 164,
  &descriptor_table_parameter_5fserver_2eproto_once, descriptor_table_parameter_5fserver_2eproto_sccs, descriptor_table_parameter_5fserver_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_parameter_5fserver_2eproto::offsets,
  file_level_metadata_parameter_5fserver_2eproto, 2, file_level_enum_descriptors_parameter_5fserver_2eproto, file_level_service_descriptors_parameter_5fserver_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_parameter_5fserver_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_parameter_5fserver_2eproto)), true);
namespace task {

// ===================================================================

void ParametersOrGradients::InitAsDefaultInstance() {
}
class ParametersOrGradients::_Internal {
 public:
  using HasBits = decltype(std::declval<ParametersOrGradients>()._has_bits_);
};

ParametersOrGradients::ParametersOrGradients()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:task.ParametersOrGradients)
}
ParametersOrGradients::ParametersOrGradients(const ParametersOrGradients& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      pairs_(from.pairs_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:task.ParametersOrGradients)
}

void ParametersOrGradients::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ParametersOrGradients_parameter_5fserver_2eproto.base);
}

ParametersOrGradients::~ParametersOrGradients() {
  // @@protoc_insertion_point(destructor:task.ParametersOrGradients)
  SharedDtor();
}

void ParametersOrGradients::SharedDtor() {
}

void ParametersOrGradients::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ParametersOrGradients& ParametersOrGradients::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ParametersOrGradients_parameter_5fserver_2eproto.base);
  return *internal_default_instance();
}


void ParametersOrGradients::Clear() {
// @@protoc_insertion_point(message_clear_start:task.ParametersOrGradients)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  pairs_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

const char* ParametersOrGradients::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .task.KeyValuePair pairs = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_pairs(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ParametersOrGradients::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:task.ParametersOrGradients)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .task.KeyValuePair pairs = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_pairs_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_pairs(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:task.ParametersOrGradients)
  return target;
}

size_t ParametersOrGradients::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:task.ParametersOrGradients)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .task.KeyValuePair pairs = 1;
  total_size += 1UL * this->_internal_pairs_size();
  for (const auto& msg : this->pairs_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ParametersOrGradients::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:task.ParametersOrGradients)
  GOOGLE_DCHECK_NE(&from, this);
  const ParametersOrGradients* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ParametersOrGradients>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:task.ParametersOrGradients)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:task.ParametersOrGradients)
    MergeFrom(*source);
  }
}

void ParametersOrGradients::MergeFrom(const ParametersOrGradients& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:task.ParametersOrGradients)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  pairs_.MergeFrom(from.pairs_);
}

void ParametersOrGradients::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:task.ParametersOrGradients)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ParametersOrGradients::CopyFrom(const ParametersOrGradients& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:task.ParametersOrGradients)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ParametersOrGradients::IsInitialized() const {
  return true;
}

void ParametersOrGradients::InternalSwap(ParametersOrGradients* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  pairs_.InternalSwap(&other->pairs_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ParametersOrGradients::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void KeyValuePair::InitAsDefaultInstance() {
}
class KeyValuePair::_Internal {
 public:
  using HasBits = decltype(std::declval<KeyValuePair>()._has_bits_);
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_dim(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

KeyValuePair::KeyValuePair()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:task.KeyValuePair)
}
KeyValuePair::KeyValuePair(const KeyValuePair& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      shape_(from.shape_),
      values_(from.values_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_name()) {
    name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  dim_ = from.dim_;
  // @@protoc_insertion_point(copy_constructor:task.KeyValuePair)
}

void KeyValuePair::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_KeyValuePair_parameter_5fserver_2eproto.base);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  dim_ = 0u;
}

KeyValuePair::~KeyValuePair() {
  // @@protoc_insertion_point(destructor:task.KeyValuePair)
  SharedDtor();
}

void KeyValuePair::SharedDtor() {
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void KeyValuePair::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const KeyValuePair& KeyValuePair::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_KeyValuePair_parameter_5fserver_2eproto.base);
  return *internal_default_instance();
}


void KeyValuePair::Clear() {
// @@protoc_insertion_point(message_clear_start:task.KeyValuePair)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  shape_.Clear();
  values_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    name_.ClearNonDefaultToEmptyNoArena();
  }
  dim_ = 0u;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

const char* KeyValuePair::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "task.KeyValuePair.name");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 dim = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_dim(&has_bits);
          dim_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated uint32 shape = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          ptr -= 1;
          do {
            ptr += 1;
            _internal_add_shape(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<24>(ptr));
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt32Parser(_internal_mutable_shape(), ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated float values = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 37)) {
          ptr -= 1;
          do {
            ptr += 1;
            _internal_add_values(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr));
            ptr += sizeof(float);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<37>(ptr));
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedFloatParser(_internal_mutable_values(), ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KeyValuePair::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:task.KeyValuePair)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "task.KeyValuePair.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  // optional uint32 dim = 2;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_dim(), target);
  }

  // repeated uint32 shape = 3;
  for (int i = 0, n = this->_internal_shape_size(); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_shape(i), target);
  }

  // repeated float values = 4;
  for (int i = 0, n = this->_internal_values_size(); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(4, this->_internal_values(i), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:task.KeyValuePair)
  return target;
}

size_t KeyValuePair::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:task.KeyValuePair)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated uint32 shape = 3;
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      UInt32Size(this->shape_);
    total_size += 1 *
                  ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_shape_size());
    total_size += data_size;
  }

  // repeated float values = 4;
  {
    unsigned int count = static_cast<unsigned int>(this->_internal_values_size());
    size_t data_size = 4UL * count;
    total_size += 1 *
                  ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_values_size());
    total_size += data_size;
  }

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional string name = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_name());
    }

    // optional uint32 dim = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->_internal_dim());
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KeyValuePair::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:task.KeyValuePair)
  GOOGLE_DCHECK_NE(&from, this);
  const KeyValuePair* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KeyValuePair>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:task.KeyValuePair)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:task.KeyValuePair)
    MergeFrom(*source);
  }
}

void KeyValuePair::MergeFrom(const KeyValuePair& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:task.KeyValuePair)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  shape_.MergeFrom(from.shape_);
  values_.MergeFrom(from.values_);
  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (cached_has_bits & 0x00000002u) {
      dim_ = from.dim_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void KeyValuePair::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:task.KeyValuePair)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KeyValuePair::CopyFrom(const KeyValuePair& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:task.KeyValuePair)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KeyValuePair::IsInitialized() const {
  return true;
}

void KeyValuePair::InternalSwap(KeyValuePair* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  shape_.InternalSwap(&other->shape_);
  values_.InternalSwap(&other->values_);
  name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(dim_, other->dim_);
}

::PROTOBUF_NAMESPACE_ID::Metadata KeyValuePair::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace task
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::task::ParametersOrGradients* Arena::CreateMaybeMessage< ::task::ParametersOrGradients >(Arena* arena) {
  return Arena::CreateInternal< ::task::ParametersOrGradients >(arena);
}
template<> PROTOBUF_NOINLINE ::task::KeyValuePair* Arena::CreateMaybeMessage< ::task::KeyValuePair >(Arena* arena) {
  return Arena::CreateInternal< ::task::KeyValuePair >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>