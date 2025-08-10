#pragma once

#include <array>
#include <limits>
#include <type_traits>
#include <vector>

class ISparseSet
{
public:
    using EntryID = uint64_t;
    static constexpr EntryID NULL_ENTRY_ID = std::numeric_limits<EntryID>::max();

    virtual ~ISparseSet() = default;
    virtual void remove(EntryID entity_id) = 0;
    virtual bool contains(EntryID entity_id) const = 0;
    virtual std::vector<EntryID> const& getRegisteredIDs() const = 0;
};

template <typename Type>
class SparseSet : public ISparseSet
{
public:
    SparseSet()
    {
        static constexpr size_t INITIAL_CAPACITY = 1028;
        m_entries.reserve(INITIAL_CAPACITY);
        m_entry_to_entity.reserve(INITIAL_CAPACITY);

        std::fill(m_entity_to_entry.begin(), m_entity_to_entry.end(), NULL_INDEX);
    };

    template <typename... Args>
    void add(EntryID entity_id, Args&&... constructor_args)
    {
        static_assert(std::is_constructible_v<Type, Args...>, 
            "Cannot construct entry with given arguments");

        m_entries.push_back(Type(std::forward(constructor_args)...));
        m_entity_to_entry[entity_id] = m_entries.size() - 1;

        m_entry_to_entity.push_back(entity_id);
    }

    Type* get(EntryID entity_id)
    {
        size_t const index = m_entity_to_entry[entity_id];
        if (index == NULL_INDEX)
            return nullptr;

        return &m_entries[index];
    }

    void remove(EntryID entity_id) final
    {
        size_t const deleted_index = m_entity_to_entry[entity_id];
        m_entries[deleted_index] = std::move(m_entries.back());

        EntryID const moved_entity = m_entry_to_entity.back();

        m_entity_to_entry[moved_entity] = deleted_index;
        m_entry_to_entity[deleted_index] = moved_entity;

        m_entries.pop_back();
        m_entity_to_entry[deleted_index] = NULL_INDEX;
        m_entry_to_entity.pop_back();
    }

    bool contains(EntryID entity_id) const final
    {
        return m_entity_to_entry[entity_id] != NULL_INDEX;
    }

    std::vector<Type>& getEntries()
    {
        return m_entries;
    }

    std::vector<EntryID> const& getRegisteredIDs() const final
    {
        return m_entry_to_entity;
    }

private:
    static constexpr size_t NULL_INDEX = std::numeric_limits<size_t>::max();

    // TODO: This needs to be improved. Pagination?
    std::array<size_t, 1'000'000> m_entity_to_entry;
    std::vector<EntryID> m_entry_to_entity;
    std::vector<Type> m_entries;
};