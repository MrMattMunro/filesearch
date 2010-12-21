package com.searchlocal.lucene;

import java.io.IOException;

import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.Term;

import com.searchlocal.dao.BaseDao;
import com.searchlocal.util.CLogger;

/**
 * 索引更新操作类
 * 
 * <p>Title: 索引更新操作</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CurrentIndexUtil {
	
	/** 日志 */
	private static CLogger logger = new CLogger(CurrentIndexUtil.class);
	
	/** Dao基类 */
	private static BaseDao dao = new BaseDao();

	/**
	 * 构造器
	 */
	public CurrentIndexUtil() {
		super();
	}
	
	/**
	 * 根据文件路径删除索引文件中内容
	 * 
	 * @param dir 索引路径
	 * @param path 需要删除的文件路径
	 */
	public static void deleteDcoumentByPath(String searcher, String path) {
		try {
			// 删除
			IndexReaderFactory indexWriterFactory = new IndexReaderFactory();
			indexWriterFactory.deleteDocuments(searcher, new Term("path", path));
		} catch (CorruptIndexException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
//	/**
//	 * 根据文件路径把文件追加索引
//	 * 
//	 * @param dir 索引路径
//	 * @param path 需要删除的文件路径
//	 * @throws Exception 
//	 */
//	public static void makeIndexByPath(String dir, String namespace, String path)  {
//		try {
//			String suffixname = StringUtils.suffixName(path);
//			String table = StringUtils.getTableName(suffixname);
//			
//			List<String> docTypes = new ArrayList<String>();
//			docTypes.add(suffixname);
//			String sql = SqlUtil.getsql(namespace, table, "selectRecordByPath");
//			
//			System.out.println("sql:" + sql);
//		
//			//锁住文件
//			Sync writerlock = IndexWriterFactory.lock.writeLock();
//			writerlock.acquire();
//			// 设置索引写工具
//			IndexWriterFactory indexWriterFactory = new IndexWriterFactory();
//			IndexWriter indexWriter = indexWriterFactory.getWriter(namespace);
//			System.out.println("writer is null::" + indexWriter == null);
//			
//			// 取得连接
//			Connection conn = dao.getConn(namespace);
//			
//            if (suffixname.equals(Constant.FileClassify.DOC)) {
//            	IndexMaker.makeWordindex(indexWriter, sql, path, conn);
//			}
//			if (suffixname.equals(Constant.FileClassify.XLS)) {
//		    	IndexMaker.makeExcelindex(indexWriter, sql, path, conn);
//			}
//			if (suffixname.equals(Constant.FileClassify.PDF)) {
//		    	IndexMaker.makePdfindex(indexWriter, sql, path, conn);
//			}
//			if (suffixname.equals(Constant.FileClassify.PPT)) {
//		    	IndexMaker.makePptindex(indexWriter, sql, path, conn);
//			}
//			if (suffixname.equals(Constant.FileClassify.CHM)) {
//		    	IndexMaker.makeChmindex(indexWriter, sql, path, conn);
//			}
//			if (Constant.FileClassify.isHtmlcontain(suffixname)) {
//		    	IndexMaker.makeHtmlindex(indexWriter, sql, path, conn);
//			}
//			if (Constant.SrcClassify.iscontain(suffixname)) {
//		    	IndexMaker.makeTxtindex(indexWriter, sql, path, conn);
//			}
//			
//	        //写入磁盘
//			if(indexWriter != null){
//				indexWriter.optimize();
//				indexWriter.commit();
//			}
//			writerlock.release();
//		} catch (LogicException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}catch (DBException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}catch (CorruptIndexException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//	}
	
}
