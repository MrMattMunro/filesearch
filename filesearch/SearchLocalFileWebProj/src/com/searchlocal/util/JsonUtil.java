
package com.web.searchlocal.util;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.beanutils.PropertyUtils;

import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import net.sf.json.xml.XMLSerializer;

/**
 * <p>Title: JSON处理类</p>
 * <p>Description:Json处理工具类 </p>
 * 
 * @author 昌 松
 * @version 1.0
 */
public class JsonUtil {
	
	
	/**
	 * 将业务数据List转换成Json字符串
	 * 
	 * @return json串 如： {"rows":[{},{}],"totalCount":10}
	 */
	public static Object json2Vo(String json, Class clz){
    	JSONObject jsonObject = JSONObject.fromObject( json );     
    	return JSONObject.toBean( jsonObject, clz );  
	}
	
	/**
	 * 将业务数据List转换成Json字符串
	 * @return json串 如： {"rows":[{},{}],"totalCount":10}
	 */
	public static String voList2JsonStringForGrid(List list){
        
        Map testmap = new HashMap();
        testmap.put("rows", (Object)list);
        testmap.put("totalCount", (Object)new Integer(list.size()));
		JSONArray json = JSONArray.fromObject(list); 
		return  json.toString();
	}
	
	/**
	 * 将业务数据List转换成Json字符串
	 * @return json串 
	 */
	public static String voList2JsonString(List list){
		
	    // json = "{'metaData':{'root':'rows','successProperty':'success','fields':[{'name':'ymonth','type':'string'}]},'success':true,'rows':[{'ymonth':'2011-08'},{'ymonth':'2011-06'}],'error_msg':''}";

		//String json = JsonUtil.voList2JsonString(tempMonthList);
        Map map = new HashMap();
	    
		JSONArray json = JSONArray.fromObject(list); 
		return  json.toString();
	}
	
	/**
	 * 
	 * 取得实体对象的Map
	 * 
	 * @return 实体对象的值
	 */
	public static Map getMetaData(Object obj){
        Map map = new HashMap();
        map.put("root", "rows");
        // 取得Object的属性定义
        Field[] fields = obj.getClass().getDeclaredFields();
        List tempList = new ArrayList();
        for(int i=0;i<fields.length;i++){
        	String name = fields[i].getName();
        	String type = "String";
			try {
				type = PropertyUtils.getPropertyType(obj, name).getName();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
				e.printStackTrace();
			}
         	Map fieldMap = new HashMap();
        	fieldMap.put("name", name);
         	fieldMap.put("type", type);
         	tempList.add(fieldMap);
        }
        map.put("fields", tempList);
        
        Map summap = new HashMap();
        summap.put("metaData", map);
        // json = "{'metaData':{'root':'rows','fields':[{'name':'ymonth','type':'string'}]},
		return  summap;
	}
	
	/**
	 * 将实体VO Object 或者 JavaBean换成Json字符串
	 * @param vo
	 * @return
	 */
	public static String vo2JsonString(Object vo){
        JSONObject json = JSONObject.fromObject(vo); 
		return  json.toString();
	}
	
	/**
	 * 将XML转换成Json字符串
	 * 
	 * @return json串 如： {"rows":[{},{}],"totalCount":10}
	 */
	public static String xml2JsonString(String xml){
		XMLSerializer xmlSerializer = new XMLSerializer();
		JSONObject  json = (JSONObject) xmlSerializer.read(xml);     
        return "[" + json.toString() + "]";
	}
	
	/**
	 * 返回数据更新成功信息
	 *
	 * @return 
	 */
	public static String success(){
		return "{success:true}";
	}
	
	/**
	 * 返回数据更新失败信息
	 *
	 * @return 
	 */
	public static String failure(String errorMessage){
		return "{failure:true,description:'"+errorMessage+"'}";
	}
}
