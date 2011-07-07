package com.searchlocal.lucene;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import net.paoding.analysis.analyzer.PaodingAnalyzer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.store.FSDirectory;

import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.XMLConfig;

/**
 * <p>
 * Lucene同一时刻只容许一个IndexWriter被打开。然而多个线程可以使用同一个IndexWriter
 * IndexWriter类管理全局IndexWriter实例
 * </p>
 * 
 * <p>
 * 当IndexWriter 或 IndexReader已经被写锁时，IndexReaders能够使用但不能做删除操作。
 * 如果共享IndexWriter被打开，并行添加操作是可以的
 * </p>
 * 
 */
public class IndexWriterFactory {

	private static Log logger = LogFactory.getLog(IndexWriterFactory.class);

	private static Map<String, IndexWriterData> writerLookup = new ConcurrentHashMap<String, IndexWriterData> ();

	private static final int LUCENE_MAX_BUFFER_SIZE = 2000;

	private static final int OPTIMIZE_INTERVAL = 200;

	private static List<CreateNewParam> searches = new ArrayList<CreateNewParam>();

	/**
	 * 初始化
	 * 
	 * @return
	 * @throws IOException
	 */
	public IndexWriterFactory() {
		try {
			if (searches.size() == 0) {
				// 取得搜索信息
				XMLConfig xmlconfig = new XMLConfig();
				searches = xmlconfig.getEntityList();
				IndexWriter writer = null;
				try {
					IndexWriterData writerData = null;
					FSDirectory directory = null;
					for (int i = 0; i < searches.size(); i++) {
						CreateNewParam createNewParm = (CreateNewParam) searches.get(i);
						String indexpath = createNewParm.getIndexpath();
						File indexDir = new File(indexpath);
						File segments = new File(indexDir + File.separator + "segments.gen");
						boolean bcreate = !segments.exists();

						directory = FSDirectory.open(new File(indexpath));
						if (writerData == null) {
							Analyzer analyzer = new PaodingAnalyzer();
							// 如果文件锁住，则主动打开
							if (IndexReader.indexExists(directory)) {
								if (IndexWriter.isLocked(directory)) {
									IndexWriter.unlock(directory);
								}
							}
							writer = new IndexWriter(directory, analyzer, bcreate,
									IndexWriter.MaxFieldLength.LIMITED);
							writer.setMaxBufferedDocs(LUCENE_MAX_BUFFER_SIZE);
							writerData = new IndexWriterData(writer, 0);
							writerLookup.put(createNewParm.getSearchname(), writerData);
						}
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
	 * 创建IndexWriter对象
	 * 
	 * @param module
	 *            模块的标识符
	 * @param create
	 *            是否重新创建索引
	 * @return
	 * @throws IOException
	 */
	public static synchronized IndexWriter getWriter(String module) {
		IndexWriter writer = null;
		IndexWriterData writerData = null;
		try {
			for (int i = 0; i < searches.size(); i++) {
				CreateNewParam createNewParm = (CreateNewParam) searches.get(i);
				if (module.equals(createNewParm.getSearchname())) {
					writerData = (IndexWriterData) writerLookup.get(module);
					if (writerData == null) {
						String indexpath = createNewParm.getIndexpath();
						File indexDir = new File(indexpath);
						File segments = new File(indexDir + File.separator + "segments.gen");
						boolean bcreate = !segments.exists();
						FSDirectory directory = FSDirectory.open(new File(indexpath));
						Analyzer analyzer = new PaodingAnalyzer();
						// // 如果文件锁住，则主动打开
						if (IndexReader.indexExists(directory)) {
							if (IndexWriter.isLocked(directory)) {
								IndexWriter.unlock(directory);
							}
						}
						writer = new IndexWriter(directory, analyzer, bcreate,
								IndexWriter.MaxFieldLength.LIMITED);
						writer.setMaxBufferedDocs(LUCENE_MAX_BUFFER_SIZE);
						writerData = new IndexWriterData(writer, 0);
						writerLookup.put(createNewParm.getSearchname(), writerData);
					}
				}
			}
			writer = writerData.getWriter();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return writer;
	}

	/**
	 * @param module
	 * @param term
	 * @throws InterruptedException
	 * @throws IOException
	 */
	public static void optimize(IndexWriter writer) throws InterruptedException, IOException {
		Collection<IndexWriterData> writers = writerLookup.values();
		for (Iterator iter = writers.iterator(); iter.hasNext();) {
			IndexWriterData writerdata = (IndexWriterData) iter.next();
			IndexWriter temp = writerdata.getWriter();
			if (temp.equals(writer)) {
				int count = writerdata.getCount();
				count = count + 1;
				writerdata.setCount(count);
				if (count > OPTIMIZE_INTERVAL) {
					writer.optimize();
					writerdata.setCount(0);
				}
			}
		}
	}

	/**
	 * @param module
	 * @param term
	 * @throws InterruptedException
	 * @throws IOException
	 */
	public static void removeIndexWriter(String namespace) throws InterruptedException, IOException {
		writerLookup.remove(namespace);
	}

	/**
	 * @param module
	 * @param term
	 * @throws InterruptedException
	 * @throws IOException
	 */
	public void clear() throws InterruptedException, IOException {
		Collection<IndexWriterData> writers = writerLookup.values();
		for (Iterator iter = writers.iterator(); iter.hasNext();) {
			IndexWriterData writerdata = (IndexWriterData) iter.next();
			IndexWriter temp = writerdata.getWriter();
			temp.close(true);
		}
		searches.clear();
		writerLookup.clear();
	}

}
