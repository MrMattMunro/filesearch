package com.web.searchlocal.service.impl;

import java.io.IOException;
import java.sql.Connection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import com.web.searchlocal.bean.SearcherBean;
import com.web.searchlocal.dao.SearcherDao;
import com.web.searchlocal.exception.DBException;
import com.web.searchlocal.exception.LogicException;
import com.web.searchlocal.factory.SearcherFactory;
import com.web.searchlocal.lucene.ContentSearcher;
import com.web.searchlocal.param.CreateNewParam;
import com.web.searchlocal.param.SearchParam;
import com.web.searchlocal.service.SearchService;

/**
 * 检索索引文件接口的实现
 * 
 * <p>Title: 检索索引文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearchServiceImpl implements SearchService {

	/**
	 * 根据关键字检索
	 * 
	 * @param param
	 * @return 结果集
	 * @throws LogicException
	 * @throws IOException
	 */
	public List dosearcher(SearchParam param) throws IOException, LogicException {
		String indexpath = getIndexpath(param.getId());
		return ContentSearcher.queryAll(param, indexpath);
	}

	/**
	 * 根据关键字检索能取得的总条数
	 * 
	 * @param param
	 * @return 总条数
	 * @throws IOException
	 * @throws LogicException 
	 */
	public int getCount(SearchParam param) throws IOException, LogicException {
		String indexpath = getIndexpath(param.getId());
		int count = ContentSearcher.getCount(param, indexpath);
		return count;
	}
	
	/**
	 * 取得所有的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws LogicException
	 * @throws IOException
	 * @throws DBException 
	 */
	public List<CreateNewParam> getAllSearcher(Connection conn) throws IOException, LogicException, DBException{
		SearcherDao searcherDao = new SearcherDao();
		List<SearcherBean> searchers = searcherDao.getAllSeacher(conn);
	    List<CreateNewParam> returnList = new ArrayList<CreateNewParam>();
		for (Iterator<SearcherBean> iter = searchers.iterator(); iter.hasNext();) {
			SearcherBean element = (SearcherBean) iter.next();
			CreateNewParam param = new CreateNewParam();
			param.setId(element.getId());
			param.setPath(element.getPath());
			param.setSelectfiletype(Arrays.asList(element.getFileType().split(",")));
			param.setIdexpath(element.getIndexPath());
			returnList.add(param);
		}
		return returnList;
	}

	/**
	 * 取得Index的目录
	 * 
	 * @param id 索引对象Id
	 * @return 索引文件目录
	 * @throws IOException
	 */
	private String getIndexpath(String id) {
		List<CreateNewParam> entityList = SearcherFactory.getSearcher();
		String indexpath = "";
		for (Iterator<CreateNewParam> iter = entityList.iterator(); iter.hasNext();) {
			CreateNewParam element = (CreateNewParam) iter.next();
			if (element.getId().equals(id)) {
				indexpath = element.getIdexpath();
			}
		}
		return indexpath;
	}
}
