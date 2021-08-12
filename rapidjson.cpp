#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include <iostream>
#include <string>
#include <stdio.h>

//https://blog.csdn.net/lk142500/article/details/80350929

using namespace std;
using namespace  rapidjson;


string readfile(const char *filename){
    FILE *fp = fopen(filename, "rb");
    if(!fp){
        printf("open failed! file: %s", filename);
        return "";
    }
    
    char *buf = new char[1024*16];
    int n = fread(buf, 1, 1024*16, fp);
    fclose(fp);
    
    string result;
    if(n>=0){
        result.append(buf, 0, n);
    }
    delete []buf;
    return result;
}


string json = "{\"te\":1}";
void Serialize_1()
{
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

    writer.StartObject();

	//Value contact(kObject);

	writer.Key("te");
    writer.String(json.c_str());
	
    //1. 整数类型
    writer.Key("Int");
    writer.Int(1);

    //2. 浮点类型
    writer.Key("Double");
    writer.Double(12.0000001);

    //3. 字符串类型
    writer.Key("String");
    writer.String("This is a string");

    //4. 结构体类型
    writer.Key("Object");
    writer.StartObject();
    writer.Key("name");
    writer.String("qq849635649");
    writer.Key("age");
    writer.Int(25);
    writer.EndObject();

    //5. 数组类型
    //5.1 整型数组
    writer.Key("IntArray");
    writer.StartArray();
    //顺序写入即可
    writer.Int(10);
    writer.Int(20);
    writer.Int(30);
    writer.EndArray();

    //5.2 浮点型数组
    writer.Key("DoubleArray");
    writer.StartArray();
    for(int i = 1; i < 4; i++)
    {
        writer.Double(i * 1.0);
    }
    writer.EndArray();

    //5.3 字符串数组
    writer.Key("StringArray");
    writer.StartArray();
    writer.String("one");
    writer.String("two");
    writer.String("three");
    writer.EndArray();

    //5.4 混合型数组
    //这说明了，一个json数组内容是不限制类型的
    writer.Key("MixedArray");
    writer.StartArray();
    writer.String("one");
    writer.Int(50);
    writer.Bool(false);
    writer.Double(12.005);
    writer.EndArray();

    //5.5 结构体数组
    writer.Key("People");
    writer.StartArray();
    for(int i = 0; i < 3; i++)
    {
        writer.StartObject();
        writer.Key("name");
        writer.String("qq849635649");
        writer.Key("age");
        writer.Int(i * 10);
        writer.Key("sex");
        writer.Bool((i % 2) == 0);
        writer.EndObject();
    }
    writer.EndArray();

    writer.EndObject();

    string data = strBuf.GetString();
    cout << data << endl;
}

int te()
{
	
	//rapidjson::Value array(rapidjson::kArrayType);                 ///< 创建一个数组对象
	//rapidjson::Value object(rapidjson::kObjectType); 
 
 
	rapidjson::Document d1,d2;
	rapidjson::Document::AllocatorType& a = d1.GetAllocator();
	Value root(kObjectType);
	

	const char* json = "{\"project\":{\"hello\":\"world\"},\"stars\":10}";  
	d1.Parse(json);
	d2.Parse(json);
	
	root.AddMember("object1", d1, a);
	root.AddMember("object2", d2, a);
	
	
	
	StringBuffer buffer;  
	Writer<StringBuffer> writer(buffer);  
	
	root.Accept(writer);  

	std::cout << buffer.GetString() << std::endl; 
}




int te2()
{
	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";  
	
	
	Document d,d1; // Null
	
	d1.Parse(json);
	
	rapidjson::Document::AllocatorType& a = d.GetAllocator();
	d.SetObject();
	Value v; // Null
	v.SetInt(10);
	v = 10; // 简写，和上面的相同
	
	//v.SetObject(d);
	
	//d.SetArray().PushBack(v, a).PushBack(v, a);
	
	Value v2;
	v2.CopyFrom(d1, a);
	d.CopyFrom(v2, a);
	//v.SetObject().AddMember("array", v2, a);
	//d.PushBack(v, a);
	
	StringBuffer buffer;  
	Writer<StringBuffer> writer(buffer);  
	
	d.Accept(writer);  
	
	// Output {"project":"rapidjson","stars":11}  
	std::cout << buffer.GetString() << std::endl; 
	
}

int te3()
{
	    Document document;
    //获得分配器
    Document::AllocatorType& allocator = document.GetAllocator();
    //root为kObjectType
    Value root(kObjectType);
    //storage_photo_count为Value的String类型，注意定义的格式
    Value storage_photo_count(kStringType);
    //使用std::string类型的构造方式创建了一个std::string值
    std::string storage_photo_count_str("49");
    //通过Value的SetString方法把一个std::string类型对象的内容赋值给了rapidjson的String对象
    storage_photo_count.SetString(storage_photo_count_str.c_str(),
    storage_photo_count_str.size(),allocator);
    Value storage_music_count(kStringType);
    std::string storage_music_count_str("48");
    storage_music_count.SetString(storage_music_count_str.c_str(),
    storage_music_count_str.size(),allocator);
    //root为对象，添加成员的方式具有allocator，一个字符串字面值，一个Value(kStringType)
    root.AddMember("storage.photo.count",storage_photo_count,allocator);
    root.AddMember("storage.music.count",storage_music_count,allocator);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);
    std::string result = buffer.GetString();
    cout << "result: " << result << "..........:" << result.size()<< endl;
}

int add_jobj()
{
	//原始json parse Document
	rapidjson::Document d_dst;
	const char* json_dst = "{\"project\":{\"start\":\"1\",\"end\":\"2\"},\"stars\":10}";  
	d_dst.Parse(json_dst);
	
	//增加json parse  Document 
	rapidjson::Document d_src;
	const char* json_src = "{\"hello\":\"world\",\"end\":\"2\"}";
	rapidjson::Document::AllocatorType& a = d_src.GetAllocator();
	d_src.Parse(json_src);
	
	//添加开始
	d_dst["project"].AddMember("haha", d_src, a);;
	
	//json Document 转 string 
	StringBuffer buffer;  
	Writer<StringBuffer> writer(buffer);  
	d_dst.Accept(writer);  
	std::cout << buffer.GetString() << std::endl; 
}

int nef()
{
	
	//原始json parse Document
	rapidjson::Document d_dst;
	const char* json_dst = "{\"project\":{\"start\":\"1\",\"end\":\"2\"},\"appIds\":[1,2,3]}";  
	d_dst.Parse(readfile("nwdaf_subevent").c_str());
	
	
	rapidjson::Document document;
    document.SetObject();
	// 添加name, value
    const char* name = "success_url";
    const char* value = "https://www.google.com";
    //document.AddMember(rapidjson::StringRef(name), rapidjson::StringRef(value), document.GetAllocator());

	if(!d_dst.HasMember("eventSubscriptions"))
		return -1;

	Value eventsSubs(kArrayType);
	
	if(d_dst["eventSubscriptions"].IsArray())
	{
		for (int i = 0; i < d_dst["eventSubscriptions"].Size(); i++)
		{
			Value eventsSubsobj(kObjectType);
			Value eventFilterobj(kObjectType);
			
			Value tgtUeobj(kObjectType);
			
			if(d_dst["eventSubscriptions"][i].HasMember("tgtUe")){
				if(d_dst["eventSubscriptions"][i]["tgtUe"].HasMember("supis"))
					tgtUeobj.AddMember(StringRef("supis"), d_dst["eventSubscriptions"][i]["tgtUe"]["supis"], document.GetAllocator());
				
				if(d_dst["eventSubscriptions"][i]["tgtUe"].HasMember("intGroupIds"))
					tgtUeobj.AddMember(StringRef("interGroupIds"), d_dst["eventSubscriptions"][i]["tgtUe"]["intGroupIds"], document.GetAllocator());
				if(d_dst["eventSubscriptions"][i]["tgtUe"].HasMember("anyUe"))
					tgtUeobj.AddMember(StringRef("anyUeId"), d_dst["eventSubscriptions"][i]["tgtUe"]["anyUe"], document.GetAllocator());
				eventFilterobj.AddMember(StringRef("tgtUe"), tgtUeobj, document.GetAllocator());
			}
			if(d_dst["eventSubscriptions"][i].HasMember("appIds"))
				eventFilterobj.AddMember(StringRef("appIds"), d_dst["eventSubscriptions"][i]["appIds"], document.GetAllocator());
			if(d_dst["eventSubscriptions"][i].HasMember("networkArea"))
				eventFilterobj.AddMember(StringRef("locArea"), d_dst["eventSubscriptions"][i]["networkArea"], document.GetAllocator());
			if(d_dst["eventSubscriptions"][i].HasMember("event"))
				eventsSubsobj.AddMember(StringRef("event"),  d_dst["eventSubscriptions"][i]["event"], document.GetAllocator());
			eventsSubsobj.AddMember(StringRef("eventFilter"), eventFilterobj, document.GetAllocator());
			eventsSubs.PushBack(eventsSubsobj, document.GetAllocator());
		}
	}
	document.AddMember(rapidjson::StringRef("eventsSubs"), eventsSubs, document.GetAllocator());
	
	if(d_dst.HasMember("evtReq"))
		document.AddMember(rapidjson::StringRef("eventsRepInfo"), d_dst["evtReq"], document.GetAllocator());
	if(d_dst.HasMember("notificationURI"))
		document.AddMember(rapidjson::StringRef("notifUri"), d_dst["notificationURI"], document.GetAllocator());
	if(d_dst.HasMember("notifId"));
		document.AddMember(rapidjson::StringRef("notifId"), d_dst["notifId"], document.GetAllocator());
    // 添加json object
	rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string json = std::string(buffer.GetString());
	
	std::cout << json << std::endl; 

}
int main()
{
	//nef();
	//te();
	te2();
	//te3();
	//Serialize_1();
	//add_jobj();
}