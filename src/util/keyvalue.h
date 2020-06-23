#ifndef KEYVALUE_HPP
#define KEYVALUE_HPP

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

class Keyvalue {
    int length{0};
    std::unordered_map<std::string, int> hash_table;
    std::vector<std::string> str_vector;

    template <typename U, typename = std::string>
    struct can_get_name : std::false_type {};

    template <typename U>
    struct can_get_name<U, decltype(std::declval<U>().get_name())>
        : std::true_type {};

  public:
    Keyvalue() = default;

    void populate(std::vector<std::string> v) {//making a hashtable for all initial facts
        for (auto &s : v) {
            insert<std::string>(s);
        }
        //for (const auto &abc: hash_table){
        //    std::cout<<"Key: "<<abc.first<<" Value: "<<abc.second<<"\n";
        //}
        //for(std::string abc: str_vector){
         //   std::cout<<abc<<"\n";
        //}
    }

    template <typename U>
    typename std::enable_if<can_get_name<U>::value, void>::type
    insert(U &target) {
        hash_table[target.get_name()] = length;
        str_vector.push_back(target.get_name());
        length++;
    }

    template <typename U> //This is the method (template) to be called by populate().
    typename std::enable_if<!can_get_name<U>::value, void>::type
    insert(U &target) {
        hash_table[target] = length; //each target get a position in the unordered_map (like python's dictionary)
        str_vector.push_back(target); //each target also is put in str_vector for other purposes;
        length++;
    }

    int operator[](const std::string &str) const { return hash_table.at(str); }  //the so-called operator overloading. When access the hash number of a string, just use obj["string name"].

    std::string operator[](int num) const { return str_vector.at(num); }

    int size() const { return length; }

    std::vector<std::string> get_str_vector() { return str_vector; }
};

#endif // KEYVALUE_HPP
