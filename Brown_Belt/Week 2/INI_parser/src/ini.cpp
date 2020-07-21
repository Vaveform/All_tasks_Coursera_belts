#include "ini.h"

namespace Ini{
Section& Document::AddSection(string name){
	return sections[name];
}

const Section& Document::GetSection(const string& name) const {
	return sections.at(name);
}

size_t Document::SectionCount() const {\
	return sections.size();
}


void Document::PrintSections() const {
	for(const auto& Section : sections){
		cout << "Name of section - " << Section.first << " : " << endl;
		for(const auto& pair : Section.second){
			cout << pair.first << " : " << pair.second << endl;
		}
	}
}

Document Load(istream& input){
	Document ini_doc;
//	string inserted_section;
//	// Здесь можно было завести указатель на вставляемую секцию, а затем в цикле когда вызывается метод
//	// AddSection(условие - когда в документе строка с [ и ]), который возвращает неконстантную ссылку на секцию которая модифицируется, получая ссылку
//	// на секцию и от нее брать адрес (указатель) в эту переменную. Указатель проинициализировать nullptr
//	// иначе, если работать с ссылками они будут инвалидироваться и значения не будут вставляться.
//	for(string line; getline(input, line);){
//		if(line != ""){
//			size_t pos_1 = line.find("[");
//			size_t pos_2 = line.find("]", pos_1);
//			if(pos_1 != line.npos && pos_2 != line.npos){
//				inserted_section = line.substr(pos_1 + 1, pos_2 - pos_1 - 1);
//				ini_doc.AddSection(inserted_section);
//			}
//			else{
//				size_t pos_non_null = line.find_first_not_of(" ");
//				size_t pos_equal = line.find("=", pos_non_null);
//				ini_doc.AddSection(inserted_section).insert({line.substr(pos_non_null, pos_equal - pos_non_null) ,
//					line.substr(pos_equal + 1)});
//			}
//		}
//	}
	Section* ptr_to_inserted_section = nullptr;
	for(string line; getline(input, line);){
		if(line != ""){
			size_t pos_1 = line.find("[");
			size_t pos_2 = line.find("]", pos_1);
			if(pos_1 != line.npos && pos_2 != line.npos){
				ptr_to_inserted_section = &ini_doc.AddSection(line.substr(pos_1 + 1, pos_2 - pos_1 - 1));
			}
			else{
				size_t pos_non_null = line.find_first_not_of(" ");
				size_t pos_equal = line.find("=", pos_non_null);
				ptr_to_inserted_section->insert({line.substr(pos_non_null, pos_equal - pos_non_null) ,
					line.substr(pos_equal + 1)});
			}
		}
	}

	return ini_doc;
}
}




