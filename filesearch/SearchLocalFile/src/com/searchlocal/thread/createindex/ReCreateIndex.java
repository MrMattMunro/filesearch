package com.searchlocal.thread.createindex;

import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import com.searchlocal.constants.Constant;
import com.searchlocal.dao.BaseDao;
import com.searchlocal.dao.FileDao;
import com.searchlocal.lucene.IndexMaker;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.XMLConfig;

/**
 * 重新生成索引文件
 * 
 * <p>Title: 重新生成索引文件</p>
 * <p>Description: </p>
 * <p>site:www.sifile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ReCreateIndex {

	/** Dao基类 */
	private static BaseDao dao = new BaseDao();

	/**
	 * 搜索文件存入文件容器
	 * 
	 * @param param 搜索参数
	 */
	public static boolean listen() {
		try {

			// 取得搜索信息
			XMLConfig xmlconfig = new XMLConfig();
			List<CreateNewParam> searches = xmlconfig.getEntityList();
			for (Iterator<CreateNewParam> iter = searches.iterator(); iter.hasNext();) {
				CreateNewParam element = (CreateNewParam) iter.next();
				// 删除所有索引文件
				FileUtil.delFolder(element.getIndexpath(), false);
				FileDao fileDao = new FileDao();
				List<FileParam> filelist = fileDao.getFileRecord(element.getSearchname());
				Set<String> paths = new HashSet<String>();

				for (Iterator fileiter = filelist.iterator(); fileiter.hasNext();) {
					FileParam fileParam = (FileParam) fileiter.next();
					String haserror = fileParam.getError();
					if (haserror.equals(Constant.NO_ERROR)) {
						paths.add(fileParam.getPath());
					}
				}

				IndexMaker.makeindex(element.getSelectfiletype(),element.getIndexpath(), element
						.getSearchname(), paths);
			}

			// IndexWriterFactory indexWriterFactory = new IndexWriterFactory();
			// indexWriterFactory.getWriter(namespace);

		} catch (Exception e) {
			e.printStackTrace();
		}

		return true;
	}

	/**
	 * 搜索文件存入文件容器
	 * 
	 * @param param 搜索参数
	 */
	public static void checkRestartApp() {

	}
}
