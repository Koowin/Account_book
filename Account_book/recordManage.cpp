#include "header.hpp"

list <Record>::iterator RecordManage::get_first(){
	return record_list.begin();
}
list <Record>::iterator RecordManage::get_end() {
	return record_list.end();
}