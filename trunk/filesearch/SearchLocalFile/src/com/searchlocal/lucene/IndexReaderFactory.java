package com.searchlocal.lucene;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.Term;
import org.apache.lucene.store.FSDirectory;

import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.XMLConfig;

/**
 * <p>
 * Lucene同一时刻只容许一个IndexReader被打开。然而多个线程可以使用同一个IndexReader
 * IndexReader类管理全局IndexReader实例
 * </p>
 * 
 * <p>
 * 当IndexWriter 或 IndexReader已经被写锁时，IndexReaders能够使用但不能做删除操作。
 * 如果共享IndexWriter被打开，并行添加操作是可以的
 * </p>
 * 
 */
public class IndexReaderFactory {

	private static Log logger = LogFactory.getLog(IndexReaderFactory.class);

	private static Map readerLookup = new ConcurrentHashMap();

	private static List searches = new ArrayList<CreateNewParam>();

	/**
	 * 初始化
	 * 
	 * @return
	 * @throws IOException
	 */
	public IndexReaderFactory() {
		try {
			if (searches.size() == 0) {
				// 取得搜索信息
				XMLConfig xmlconfig = new XMLConfig();
				searches = xmlconfig.getEntityList();
				try {
					FSDirectory directory = null;
					for (int i = 0; i < searches.size(); i++) {
						CreateNewParam createNewParm = (CreateNewParam) searches.get(i);
						String indexpath = createNewParm.getIdexpath();
						directory = FSDirectory.open(new File(indexpath));
						IndexReader reader = IndexReader.open(directory, false);
						readerLookup.put(createNewParm.getSearchname(), reader);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		} catch (Exception se) {
			logger.error(se);
		}
	}

	/**
	 * 创建IndexReader对象
	 * 
	 * @param module
	 *            模块的标识符
	 * @return
	 * @throws IOException
	 */
	public synchronized IndexReader getReader(String module) throws IOException {
		try {
			IndexReader reader = null;
			for (int i = 0; i < searches.size(); i++) {
				CreateNewParam createNewParm = (CreateNewParam) searches.get(i);
				if (module.equals(createNewParm.getSearchname())) {
					String indexpath = createNewParm.getIdexpath();
					reader = (IndexReader) readerLookup.get(module);
					if (reader == null) {
						FSDirectory directory = FSDirectory.open(new File(indexpath));
						reader = IndexReader.open(directory, false);
						readerLookup.put(module, reader);
					}
				}
			}
			return reader;
		} catch (Exception e) {
			logger.error("Unable to create a new reader", e);
			throw new IOException("Unable to create a new writer");
		}
	}

	public void destroy() {
		Iterator<Entry<String, IndexReader>> iterator = readerLookup.entrySet().iterator();
		while (iterator.hasNext()) {
			Entry<String, IndexReader> entry = iterator.next();
			IndexReader indexReader = entry.getValue();
			try {
				indexReader.close();
				indexReader = null;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		readerLookup.clear();
	}

	/**
	 * @param module
	 * @param term
	 * @throws InterruptedException
	 * @throws IOException
	 */
	public void deleteDocuments(String module, Term term) throws InterruptedException, IOException {
		for (int i = 0; i < searches.size(); i++) {
			CreateNewParam createNewParm = (CreateNewParam) searches.get(i);
			if (module.equals(createNewParm.getSearchname())) {
				IndexReaderFactory factory = new IndexReaderFactory();
				IndexReader reader = factory.getReader(module);
				int num = reader.deleteDocuments(term);
				reader.flush();
			}
		}
	}
}
