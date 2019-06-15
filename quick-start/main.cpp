#include <iostream>
#include <fstream>

// Архивы выступают в роли посредников между кодом и сериализованными данными -
// они выполняют чтение и запись данных:
#include <cereal/archives/xml.hpp>
// #include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
// #include <cereal/archives/portable_binary.hpp>

#include "MyClass.hpp"
typedef MyClass MyData;


void SerializeData() {
  std::stringstream ss;  // можно использовать любой поток.

  // Архивы в своём конструкторе принимают std::istream или std::ostream объект.

  {
    cereal::BinaryOutputArchive oarchive(ss);  // создание выходного архива.

    MyData m1 = { 15, 6, 2019 };
    MyData m2, m3;
    m2.x = 16;
    m2.y = 6;
    m2.z = 2019;
    m3 = { 17, 6, 2019 };

    oarchive(m1, m2, m3);  // запись данных в архив.
  }  // архив выходит из скопа - гарантируется flush всего контента.

  // Архивы спроектированы по идиоме RAII и flush контента гарантируется
  // только при их деструкции. Некоторые архивы могут безопасно завершить
  // flush только при их деструкции. Нужно убедиться, особенно для выходной
  // сериализации, что архив автоматически уничтожается после завершения
  // работы с ним.

  {
    cereal::BinaryInputArchive iarchive(ss);  // создание входного архива.

    MyData m1, m2, m3;
    iarchive(m1, m2, m3);  // чтение данных из архива.

    std::cout << "m1 { x = " << m1.x << ", y = " << m1.y << ", z = " << m1.z << " }" << std::endl;
    std::cout << "m2 { x = " << m2.x << ", y = " << m2.y << ", z = " << m2.z << " }" << std::endl;
    std::cout << "m3 { x = " << m3.x << ", y = " << m3.y << ", z = " << m3.z << " }" << std::endl;

  }
}

void NamingValues() {
  {
    std::ofstream os("data.xml");
    cereal::XMLOutputArchive archive(os);

    MyData m1 = { 18, 6, 2019 };
    int someInt = 777;
    double d = 1000;

    archive( CEREAL_NVP(m1), // именовать вывод также как и имя переменной.
             someInt,        // без NVP - cereal автоматически сгенерирует численное имя.
             cereal::make_nvp("this_name_is_way_better", d) );  // указание своего имени.
             // К объектам можно прикреплять удобочитаемые имена.
  }

  {
    std::ifstream is("data.xml");
    cereal::XMLInputArchive archive(is);

    MyData m1;
    int someInt;
    double d;

    archive( m1, someInt, d ); // NVP не строго необходимы при загрузке,
                               // но могут быть использованы (даже не в том порядке???).

    std::cout << "m1 { x = " << m1.x << ", y = " << m1.y << ", z = " << m1.z << " }" << std::endl;
    std::cout << "someInt = " << someInt << std::endl;
    std::cout << "d = " << d << std::endl;
  }
}

int main() {
  std::cout << "SerializeData()" << std::endl;
  SerializeData();
  std::cout << std::endl;
  std::cout << "NamingValues()" << std::endl;
  NamingValues();

  // Также cereal может справиться с умными указателями, полиморфизмом, и
  // наследованием.

  return 0;
}
