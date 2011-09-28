package com.web.searchlocal.service;

import java.io.IOException;
import java.sql.Connection;
import java.util.List;

import com.web.searchlocal.exception.DBException;
import com.web.searchlocal.exception.LogicException;
import com.web.searchlocal.param.SearchParam;

/**
 * 检索索引文件接口
 * 
 * <p>Title: 检索索引文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public interface SearchService {
	
	/**
	 * 根据关键字检索
	 * 
	 * @param param
	 * @throws LogicException
	 * @throws IOException
	 */
	public List dosearcher(SearchParam param) throws IOException, LogicException;
	
	/**
	 * 取得所有的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws LogicException
	 * @throws IOException
	 */
	public List getAllSearcher(Connection conn) throws IOException, LogicException, DBException;
	
	
	/**
	 * 根据关键字检索能取得的总条数
	 * 
	 * @param param
	 * @throws IOException
	 */
	public int getCount(SearchParam param) throws IOException,LogicException;
}
