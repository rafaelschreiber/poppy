// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pop3client.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_pop3client_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_pop3client_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3015000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3015007 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/empty.pb.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_pop3client_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_pop3client_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[5]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_pop3client_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_pop3client_2eproto_metadata_getter(int index);
class MailList;
struct MailListDefaultTypeInternal;
extern MailListDefaultTypeInternal _MailList_default_instance_;
class MailPreview;
struct MailPreviewDefaultTypeInternal;
extern MailPreviewDefaultTypeInternal _MailPreview_default_instance_;
class MailPreviewRequest;
struct MailPreviewRequestDefaultTypeInternal;
extern MailPreviewRequestDefaultTypeInternal _MailPreviewRequest_default_instance_;
class MailPreviewResponse;
struct MailPreviewResponseDefaultTypeInternal;
extern MailPreviewResponseDefaultTypeInternal _MailPreviewResponse_default_instance_;
class MailPreview_HeaderEntry_DoNotUse;
struct MailPreview_HeaderEntry_DoNotUseDefaultTypeInternal;
extern MailPreview_HeaderEntry_DoNotUseDefaultTypeInternal _MailPreview_HeaderEntry_DoNotUse_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::MailList* Arena::CreateMaybeMessage<::MailList>(Arena*);
template<> ::MailPreview* Arena::CreateMaybeMessage<::MailPreview>(Arena*);
template<> ::MailPreviewRequest* Arena::CreateMaybeMessage<::MailPreviewRequest>(Arena*);
template<> ::MailPreviewResponse* Arena::CreateMaybeMessage<::MailPreviewResponse>(Arena*);
template<> ::MailPreview_HeaderEntry_DoNotUse* Arena::CreateMaybeMessage<::MailPreview_HeaderEntry_DoNotUse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class MailPreview_HeaderEntry_DoNotUse : public ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<MailPreview_HeaderEntry_DoNotUse, 
    std::string, std::string,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING> {
public:
  typedef ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<MailPreview_HeaderEntry_DoNotUse, 
    std::string, std::string,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING> SuperType;
  MailPreview_HeaderEntry_DoNotUse();
  explicit constexpr MailPreview_HeaderEntry_DoNotUse(
      ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);
  explicit MailPreview_HeaderEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void MergeFrom(const MailPreview_HeaderEntry_DoNotUse& other);
  static const MailPreview_HeaderEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const MailPreview_HeaderEntry_DoNotUse*>(&_MailPreview_HeaderEntry_DoNotUse_default_instance_); }
  static bool ValidateKey(std::string* s) {
    return ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(s->data(), static_cast<int>(s->size()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE, "MailPreview.HeaderEntry.key");
 }
  static bool ValidateValue(std::string* s) {
    return ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(s->data(), static_cast<int>(s->size()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE, "MailPreview.HeaderEntry.value");
 }
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& other) final;
  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_pop3client_2eproto);
    return ::descriptor_table_pop3client_2eproto.file_level_metadata[0];
  }

  public:
};

// -------------------------------------------------------------------

class MailPreview PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MailPreview) */ {
 public:
  inline MailPreview() : MailPreview(nullptr) {}
  virtual ~MailPreview();
  explicit constexpr MailPreview(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MailPreview(const MailPreview& from);
  MailPreview(MailPreview&& from) noexcept
    : MailPreview() {
    *this = ::std::move(from);
  }

  inline MailPreview& operator=(const MailPreview& from) {
    CopyFrom(from);
    return *this;
  }
  inline MailPreview& operator=(MailPreview&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MailPreview& default_instance() {
    return *internal_default_instance();
  }
  static inline const MailPreview* internal_default_instance() {
    return reinterpret_cast<const MailPreview*>(
               &_MailPreview_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(MailPreview& a, MailPreview& b) {
    a.Swap(&b);
  }
  inline void Swap(MailPreview* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MailPreview* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MailPreview* New() const final {
    return CreateMaybeMessage<MailPreview>(nullptr);
  }

  MailPreview* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MailPreview>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MailPreview& from);
  void MergeFrom(const MailPreview& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MailPreview* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MailPreview";
  }
  protected:
  explicit MailPreview(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_pop3client_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------


  // accessors -------------------------------------------------------

  enum : int {
    kHeaderFieldNumber = 4,
    kUidlFieldNumber = 3,
    kMailidFieldNumber = 1,
    kSizeFieldNumber = 2,
  };
  // map<string, string> header = 4;
  int header_size() const;
  private:
  int _internal_header_size() const;
  public:
  void clear_header();
  private:
  const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
      _internal_header() const;
  ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
      _internal_mutable_header();
  public:
  const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
      header() const;
  ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
      mutable_header();

  // string uidl = 3;
  void clear_uidl();
  const std::string& uidl() const;
  void set_uidl(const std::string& value);
  void set_uidl(std::string&& value);
  void set_uidl(const char* value);
  void set_uidl(const char* value, size_t size);
  std::string* mutable_uidl();
  std::string* release_uidl();
  void set_allocated_uidl(std::string* uidl);
  private:
  const std::string& _internal_uidl() const;
  void _internal_set_uidl(const std::string& value);
  std::string* _internal_mutable_uidl();
  public:

  // uint32 mailid = 1;
  void clear_mailid();
  ::PROTOBUF_NAMESPACE_ID::uint32 mailid() const;
  void set_mailid(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_mailid() const;
  void _internal_set_mailid(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 size = 2;
  void clear_size();
  ::PROTOBUF_NAMESPACE_ID::uint32 size() const;
  void set_size(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_size() const;
  void _internal_set_size(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:MailPreview)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::MapField<
      MailPreview_HeaderEntry_DoNotUse,
      std::string, std::string,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING> header_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr uidl_;
  ::PROTOBUF_NAMESPACE_ID::uint32 mailid_;
  ::PROTOBUF_NAMESPACE_ID::uint32 size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_pop3client_2eproto;
};
// -------------------------------------------------------------------

class MailList PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MailList) */ {
 public:
  inline MailList() : MailList(nullptr) {}
  virtual ~MailList();
  explicit constexpr MailList(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MailList(const MailList& from);
  MailList(MailList&& from) noexcept
    : MailList() {
    *this = ::std::move(from);
  }

  inline MailList& operator=(const MailList& from) {
    CopyFrom(from);
    return *this;
  }
  inline MailList& operator=(MailList&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MailList& default_instance() {
    return *internal_default_instance();
  }
  static inline const MailList* internal_default_instance() {
    return reinterpret_cast<const MailList*>(
               &_MailList_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(MailList& a, MailList& b) {
    a.Swap(&b);
  }
  inline void Swap(MailList* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MailList* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MailList* New() const final {
    return CreateMaybeMessage<MailList>(nullptr);
  }

  MailList* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MailList>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MailList& from);
  void MergeFrom(const MailList& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MailList* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MailList";
  }
  protected:
  explicit MailList(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_pop3client_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLengthFieldNumber = 1,
    kSizeFieldNumber = 2,
  };
  // uint32 length = 1;
  void clear_length();
  ::PROTOBUF_NAMESPACE_ID::uint32 length() const;
  void set_length(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_length() const;
  void _internal_set_length(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 size = 2;
  void clear_size();
  ::PROTOBUF_NAMESPACE_ID::uint32 size() const;
  void set_size(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_size() const;
  void _internal_set_size(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:MailList)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::uint32 length_;
  ::PROTOBUF_NAMESPACE_ID::uint32 size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_pop3client_2eproto;
};
// -------------------------------------------------------------------

class MailPreviewRequest PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MailPreviewRequest) */ {
 public:
  inline MailPreviewRequest() : MailPreviewRequest(nullptr) {}
  virtual ~MailPreviewRequest();
  explicit constexpr MailPreviewRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MailPreviewRequest(const MailPreviewRequest& from);
  MailPreviewRequest(MailPreviewRequest&& from) noexcept
    : MailPreviewRequest() {
    *this = ::std::move(from);
  }

  inline MailPreviewRequest& operator=(const MailPreviewRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline MailPreviewRequest& operator=(MailPreviewRequest&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MailPreviewRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const MailPreviewRequest* internal_default_instance() {
    return reinterpret_cast<const MailPreviewRequest*>(
               &_MailPreviewRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(MailPreviewRequest& a, MailPreviewRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(MailPreviewRequest* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MailPreviewRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MailPreviewRequest* New() const final {
    return CreateMaybeMessage<MailPreviewRequest>(nullptr);
  }

  MailPreviewRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MailPreviewRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MailPreviewRequest& from);
  void MergeFrom(const MailPreviewRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MailPreviewRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MailPreviewRequest";
  }
  protected:
  explicit MailPreviewRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_pop3client_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // uint32 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint32 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:MailPreviewRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::uint32 id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_pop3client_2eproto;
};
// -------------------------------------------------------------------

class MailPreviewResponse PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MailPreviewResponse) */ {
 public:
  inline MailPreviewResponse() : MailPreviewResponse(nullptr) {}
  virtual ~MailPreviewResponse();
  explicit constexpr MailPreviewResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MailPreviewResponse(const MailPreviewResponse& from);
  MailPreviewResponse(MailPreviewResponse&& from) noexcept
    : MailPreviewResponse() {
    *this = ::std::move(from);
  }

  inline MailPreviewResponse& operator=(const MailPreviewResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline MailPreviewResponse& operator=(MailPreviewResponse&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MailPreviewResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const MailPreviewResponse* internal_default_instance() {
    return reinterpret_cast<const MailPreviewResponse*>(
               &_MailPreviewResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  friend void swap(MailPreviewResponse& a, MailPreviewResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(MailPreviewResponse* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MailPreviewResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MailPreviewResponse* New() const final {
    return CreateMaybeMessage<MailPreviewResponse>(nullptr);
  }

  MailPreviewResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MailPreviewResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MailPreviewResponse& from);
  void MergeFrom(const MailPreviewResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MailPreviewResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MailPreviewResponse";
  }
  protected:
  explicit MailPreviewResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_pop3client_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMailPreviewsFieldNumber = 1,
  };
  // repeated .MailPreview mail_previews = 1;
  int mail_previews_size() const;
  private:
  int _internal_mail_previews_size() const;
  public:
  void clear_mail_previews();
  ::MailPreview* mutable_mail_previews(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::MailPreview >*
      mutable_mail_previews();
  private:
  const ::MailPreview& _internal_mail_previews(int index) const;
  ::MailPreview* _internal_add_mail_previews();
  public:
  const ::MailPreview& mail_previews(int index) const;
  ::MailPreview* add_mail_previews();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::MailPreview >&
      mail_previews() const;

  // @@protoc_insertion_point(class_scope:MailPreviewResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::MailPreview > mail_previews_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_pop3client_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// MailPreview

// uint32 mailid = 1;
inline void MailPreview::clear_mailid() {
  mailid_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailPreview::_internal_mailid() const {
  return mailid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailPreview::mailid() const {
  // @@protoc_insertion_point(field_get:MailPreview.mailid)
  return _internal_mailid();
}
inline void MailPreview::_internal_set_mailid(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  mailid_ = value;
}
inline void MailPreview::set_mailid(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_mailid(value);
  // @@protoc_insertion_point(field_set:MailPreview.mailid)
}

// uint32 size = 2;
inline void MailPreview::clear_size() {
  size_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailPreview::_internal_size() const {
  return size_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailPreview::size() const {
  // @@protoc_insertion_point(field_get:MailPreview.size)
  return _internal_size();
}
inline void MailPreview::_internal_set_size(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  size_ = value;
}
inline void MailPreview::set_size(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_size(value);
  // @@protoc_insertion_point(field_set:MailPreview.size)
}

// string uidl = 3;
inline void MailPreview::clear_uidl() {
  uidl_.ClearToEmpty();
}
inline const std::string& MailPreview::uidl() const {
  // @@protoc_insertion_point(field_get:MailPreview.uidl)
  return _internal_uidl();
}
inline void MailPreview::set_uidl(const std::string& value) {
  _internal_set_uidl(value);
  // @@protoc_insertion_point(field_set:MailPreview.uidl)
}
inline std::string* MailPreview::mutable_uidl() {
  // @@protoc_insertion_point(field_mutable:MailPreview.uidl)
  return _internal_mutable_uidl();
}
inline const std::string& MailPreview::_internal_uidl() const {
  return uidl_.Get();
}
inline void MailPreview::_internal_set_uidl(const std::string& value) {
  
  uidl_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void MailPreview::set_uidl(std::string&& value) {
  
  uidl_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:MailPreview.uidl)
}
inline void MailPreview::set_uidl(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  uidl_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:MailPreview.uidl)
}
inline void MailPreview::set_uidl(const char* value,
    size_t size) {
  
  uidl_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:MailPreview.uidl)
}
inline std::string* MailPreview::_internal_mutable_uidl() {
  
  return uidl_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* MailPreview::release_uidl() {
  // @@protoc_insertion_point(field_release:MailPreview.uidl)
  return uidl_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void MailPreview::set_allocated_uidl(std::string* uidl) {
  if (uidl != nullptr) {
    
  } else {
    
  }
  uidl_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), uidl,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:MailPreview.uidl)
}

// map<string, string> header = 4;
inline int MailPreview::_internal_header_size() const {
  return header_.size();
}
inline int MailPreview::header_size() const {
  return _internal_header_size();
}
inline void MailPreview::clear_header() {
  header_.Clear();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
MailPreview::_internal_header() const {
  return header_.GetMap();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
MailPreview::header() const {
  // @@protoc_insertion_point(field_map:MailPreview.header)
  return _internal_header();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
MailPreview::_internal_mutable_header() {
  return header_.MutableMap();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
MailPreview::mutable_header() {
  // @@protoc_insertion_point(field_mutable_map:MailPreview.header)
  return _internal_mutable_header();
}

// -------------------------------------------------------------------

// MailList

// uint32 length = 1;
inline void MailList::clear_length() {
  length_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailList::_internal_length() const {
  return length_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailList::length() const {
  // @@protoc_insertion_point(field_get:MailList.length)
  return _internal_length();
}
inline void MailList::_internal_set_length(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  length_ = value;
}
inline void MailList::set_length(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_length(value);
  // @@protoc_insertion_point(field_set:MailList.length)
}

// uint32 size = 2;
inline void MailList::clear_size() {
  size_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailList::_internal_size() const {
  return size_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailList::size() const {
  // @@protoc_insertion_point(field_get:MailList.size)
  return _internal_size();
}
inline void MailList::_internal_set_size(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  size_ = value;
}
inline void MailList::set_size(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_size(value);
  // @@protoc_insertion_point(field_set:MailList.size)
}

// -------------------------------------------------------------------

// MailPreviewRequest

// uint32 id = 1;
inline void MailPreviewRequest::clear_id() {
  id_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailPreviewRequest::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MailPreviewRequest::id() const {
  // @@protoc_insertion_point(field_get:MailPreviewRequest.id)
  return _internal_id();
}
inline void MailPreviewRequest::_internal_set_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  id_ = value;
}
inline void MailPreviewRequest::set_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:MailPreviewRequest.id)
}

// -------------------------------------------------------------------

// MailPreviewResponse

// repeated .MailPreview mail_previews = 1;
inline int MailPreviewResponse::_internal_mail_previews_size() const {
  return mail_previews_.size();
}
inline int MailPreviewResponse::mail_previews_size() const {
  return _internal_mail_previews_size();
}
inline void MailPreviewResponse::clear_mail_previews() {
  mail_previews_.Clear();
}
inline ::MailPreview* MailPreviewResponse::mutable_mail_previews(int index) {
  // @@protoc_insertion_point(field_mutable:MailPreviewResponse.mail_previews)
  return mail_previews_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::MailPreview >*
MailPreviewResponse::mutable_mail_previews() {
  // @@protoc_insertion_point(field_mutable_list:MailPreviewResponse.mail_previews)
  return &mail_previews_;
}
inline const ::MailPreview& MailPreviewResponse::_internal_mail_previews(int index) const {
  return mail_previews_.Get(index);
}
inline const ::MailPreview& MailPreviewResponse::mail_previews(int index) const {
  // @@protoc_insertion_point(field_get:MailPreviewResponse.mail_previews)
  return _internal_mail_previews(index);
}
inline ::MailPreview* MailPreviewResponse::_internal_add_mail_previews() {
  return mail_previews_.Add();
}
inline ::MailPreview* MailPreviewResponse::add_mail_previews() {
  // @@protoc_insertion_point(field_add:MailPreviewResponse.mail_previews)
  return _internal_add_mail_previews();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::MailPreview >&
MailPreviewResponse::mail_previews() const {
  // @@protoc_insertion_point(field_list:MailPreviewResponse.mail_previews)
  return mail_previews_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_pop3client_2eproto
