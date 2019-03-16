#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

int main() {
    std::vector<int> day, product_id, customer_id;

    std::ifstream file("db.txt");
    if (!file.is_open()) {
        std::cout << "file not found !" << std::endl;
        return 0;
    }
    std::string str;
    int n = 0;
    while (std::getline(file, str))
        n++;
    file.close();
    file.open("db.txt");

    std::string *line{new std::string[n]};
    for (int i = 0; i < n; i++) {
        std::getline(file, str);
        line[i] = str;
        day.push_back(std::stoi(line[i].substr(1, 4) + line[i].substr(6, 2) + line[i].substr(9, 2)));
        product_id.push_back(std::stoi(line[i].substr(19, 3)));
        customer_id.push_back(std::stoi(line[i].substr(23, 4)));
    }

    std::vector<int> new_day, new_product_id, new_customer_id;
    new_day = day;
    new_customer_id = customer_id;
    new_product_id = product_id;
    for (int i = 0; i < day.size(); i++) {
        for (int j = i; j < day.size(); j++) {
            if (i == j)
                continue;
            if (day.size() == 1)
                break;
            if (day[i] == day[j]) {
                day.erase(day.begin() + j - 1);
                j--;
            }
        }
    }
    for (int i = 0; i < product_id.size() ; ++i) {
        for (int j = i; j < product_id.size(); ++j) {
            if (i == j)
                continue;
            if (product_id.size() == 1)
                break;
            if (product_id[i] == product_id[j]) {
                product_id.erase(product_id.begin() + j - 1);
                j--;
            }
        }
    }
    for (int i = 0; i < customer_id.size() ; ++i) {
        for (int j = i; j < customer_id.size(); ++j) {
            if (i == j)
                continue;
            if (customer_id.size() == 1)
                break;
            if (customer_id[i] == customer_id[j]) {
                customer_id.erase(customer_id.begin() + j - 1);
                j--;
            }
        }
    }

    std::sort(day.begin(),day.end());

    std::vector<std::vector<int>> customer_count,product_count;
    customer_count.resize(day.size());
    product_count.resize(day.size());
    for (int i = 0; i < day.size() ; ++i) {
        for (int j = 0 ; j < new_customer_id.size() ; ++j){
            if (day[i]== new_day[j]){
                customer_count[i].push_back(new_customer_id[j]);
                product_count[i].push_back(new_product_id[j]);
            }
        }
    }

    for (int i = 0; i < day.size() ; ++i) {
        for (int j = 0; j < product_count[i].size()  ; ++j) {
            for (int k = j; k < product_count[i].size() ; ++k) {
                if (k==j)
                    continue;
                if (product_count[i].size()==1)
                    break;
                if (product_count[i][j]==product_count[i][k]) {
                    product_count[i].erase(product_count[i].begin() + k - 1);
                    k--;
                }
            }
        }
        for (int j = 0; j < customer_count[i].size()  ; ++j) {
            for (int k = j; k < customer_count[i].size(); ++k) {
                if (k == j)
                    continue;
                if (customer_count[i].size() == 1)
                    break;
                if (customer_count[i][j] == customer_count[i][k]) {
                    customer_count[i].erase(customer_count[i].begin() + k - 1);
                    k--;
                }
            }
        }
    }

    std::ofstream new_file{"dbnew.txt"};
    for (int i = 0; i < day.size(); ++i) {
        new_file<<"["+std::to_string(day[i]).substr(0,4)<<"-";
        new_file<<std::to_string(day[i]).substr(4,2)<<"-";
        new_file<<std::to_string(day[i]).substr(6,2)<<"]";
        if (i < day.size()-1)
            new_file<<" "<<product_count[i].size()<<" "<<customer_count[i].size()<<std::endl;
        else
            new_file<<" "<<product_count[i].size()<<" "<<customer_count[i].size();
    }

    file.close();
    new_file.close();
    return 0;
}