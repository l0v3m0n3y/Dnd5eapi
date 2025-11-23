#ifndef DND5EAPI_H
#define DND5EAPI_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <vector>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Dnd5eapi {
private:
    std::string api_base = "https://www.dnd5eapi.co/api/2014";
    http_client_config client_config;
    
    http_request create_request(const std::string& endpoint, const std::string& method, const std::string& data = "") {
        http_request request;
        
        if (method == "GET") {
            request.set_method(methods::GET);
        } else if (method == "POST") {
            request.set_method(methods::POST);
        } else if (method == "PUT") {
            request.set_method(methods::PUT);
        } else if (method == "DEL") {
            request.set_method(methods::DEL);
        }
        
        request.set_request_uri(utility::conversions::to_string_t(endpoint));
        
        // Set headers
        request.headers().add(U("Host"), U("www.dnd5eapi.co"));
        request.headers().add(U("Content-Type"), U("application/json"));
        request.headers().add(U("User-Agent"), U("Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0"));
        
        if (!data.empty() && (method == "POST" || method == "PUT")) {
            request.set_body(data);
        }
        
        return request;
    }
    
    std::string build_query_params(const std::map<std::string, std::string>& params) {
        if (params.empty()) return "";
        
        std::string query = "?";
        bool first = true;
        for (const auto& param : params) {
            if (!param.second.empty()) {
                if (!first) query += "&";
                // Кодируем значения параметров
                auto encoded_value = web::uri::encode_data_string(utility::conversions::to_string_t(param.second));
                query += param.first + "=" + utility::conversions::to_utf8string(encoded_value);
                first = false;
            }
        }
        return query;
    }
    
    pplx::task<json::value> make_api_call(const std::string& endpoint, const std::string& method, const std::string& data = "") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        auto request = create_request(endpoint, method, data);

        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: ") + utility::conversions::to_string_t(std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: ") + utility::conversions::to_string_t(e.what()));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

public:
    Dnd5eapi(){
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> ability_scores(){
        return make_api_call("/ability-scores","GET");
    }
    
    pplx::task<json::value> ability_scores_by_index(const std::string& index){
        return make_api_call("/ability-scores" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> alignments(){
        return make_api_call("/alignments","GET");
    }
    
    pplx::task<json::value> alignments_by_index(const std::string& index){
        return make_api_call("/alignments" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> backgrounds(){
        return make_api_call("/backgrounds","GET");
    }
    
    pplx::task<json::value> backgrounds_by_index(const std::string& index){
        return make_api_call("/backgrounds" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> classes(){
        return make_api_call("/classes","GET");
    }
    
    pplx::task<json::value> classes_by_index(const std::string& index){
        return make_api_call("/classes" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> conditions(){
        return make_api_call("/conditions","GET");
    }
    
    pplx::task<json::value> conditions_by_index(const std::string& index){
        return make_api_call("/conditions" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> damage_types(){
        return make_api_call("/damage-types","GET");
    }
    
    pplx::task<json::value> damage_types_by_index(const std::string& index){
        return make_api_call("/damage-types" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> equipment(){
        return make_api_call("/equipment","GET");
    }
    
    pplx::task<json::value> equipment_by_index(const std::string& index){
        return make_api_call("/equipment" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> equipment_categories(){
        return make_api_call("/equipment-categories","GET");
    }
    
    pplx::task<json::value> equipment_categories_by_index(const std::string& index){
        return make_api_call("/equipment-categories" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> feats(){
        return make_api_call("/feats","GET");
    }
    
    pplx::task<json::value> feats_by_index(const std::string& index){
        return make_api_call("/feats" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> features(){
        return make_api_call("/features","GET");
    }
    
    pplx::task<json::value> features_by_index(const std::string& index){
        return make_api_call("/features" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> languages(){
        return make_api_call("/languages","GET");
    }
    
    pplx::task<json::value> languages_by_index(const std::string& index){
        return make_api_call("/languages" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> magic_items(){
        return make_api_call("/magic-items","GET");
    }
    
    pplx::task<json::value> magic_items_by_index(const std::string& index){
        return make_api_call("/magic-items" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> magic_schools(){
        return make_api_call("/magic-schools","GET");
    }
    
    pplx::task<json::value> magic_schools_by_index(const std::string& index){
        return make_api_call("/magic-schools" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> monsters(){
        return make_api_call("/monsters","GET");
    }
    
    pplx::task<json::value> monsters_by_index(const std::string& index){
        return make_api_call("/monsters" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> proficiencies(){
        return make_api_call("/proficiencies","GET");
    }
    
    pplx::task<json::value> proficiencies_by_index(const std::string& index){
        return make_api_call("/proficiencies" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> races(){
        return make_api_call("/races","GET");
    }
    
    pplx::task<json::value> races_by_index(const std::string& index){
        return make_api_call("/races" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> rule_sections(){
        return make_api_call("/rule-sections","GET");
    }
    
    pplx::task<json::value> rule_sections_by_index(const std::string& index){
        return make_api_call("/rule-sections" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> rules(){
        return make_api_call("/rules","GET");
    }
    
    pplx::task<json::value> rules_by_index(const std::string& index){
        return make_api_call("/rules" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> skills(){
        return make_api_call("/skills","GET");
    }
    
    pplx::task<json::value> skills_by_index(const std::string& index){
        return make_api_call("/skills" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    
    pplx::task<json::value> spells(){
        return make_api_call("/spells","GET");
    }
    
    pplx::task<json::value> spells_by_index(const std::string& index){
        return make_api_call("/spells" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }
    

    pplx::task<json::value> subclasses(const std::string& index){
        return make_api_call("/subclasses/"+ utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }

    pplx::task<json::value> subclasses( ){
        return make_api_call("/subclasses","GET");
    }

    pplx::task<json::value> subraces(const std::string& index){
        return make_api_call("/subraces/"+ utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }

    pplx::task<json::value> subraces( ){
        return make_api_call("/subraces","GET");
    }

    pplx::task<json::value> traits_by_index(const std::string& index){
        return make_api_call("/traits/"+ utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }

    pplx::task<json::value> traits( ){
        return make_api_call("/traits","GET");
    }

    pplx::task<json::value> weapon_properties_by_index(const std::string& index){
        return make_api_call("/weapon-properties/"+ utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(index))),"GET");
    }

    pplx::task<json::value> weapon_properties( ){
        return make_api_call("/weapon-properties","GET");
    }

};
#endif
