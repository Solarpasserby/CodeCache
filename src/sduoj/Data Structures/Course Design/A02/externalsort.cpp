/**
 * 测试数据
 * 缓存大小1000 4路归并
 * | 数据规模 | 访存次数 |
 * | ------- | -------- |
 * | 1000    | 20       |
 * | 10000   | 359      | 
 * | 100000  | 5463     | 
 * 
 * 缓存大小10000 4路归并
 * | 数据规模 | 访存次数 |
 * | ------- | -------- |
 * | 1000    | 2        |
 * | 10000   | 20       | 
 * | 100000  | 357      |
 * 
 * 缓存大小10000 8路归并
 * | 数据规模 | 访存次数 |
 * | ------- | -------- |
 * | 1000    | 2        |
 * | 10000   | 27       | 
 * | 100000  | 416      | 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>

const int BUFFER_SIZE = 1e4;
const int MERGE_WAYS = 8;

int accessCnt = 0;

template <typename T>
struct Point
{
    T val;
    int seq;

    Point(T v = T(), int s = 0) : val(v), seq(s) {}

    bool operator>(const Point &other)
    {
        if(seq > other.seq) return true;
        if(seq < other.seq) return false;
        return val > other.val;
    }
};

template <typename T>
struct LoserTree
{
    std::vector<int> tree;
    std::vector<T> data;

    LoserTree(int n = 1000) : tree(n, -1), data(n, T()) {}

    void init(const std::vector<T> &v)
    {
        data = v;
        tree.assign(v.size(), -1);
        for(int i = 0; i < v.size(); ++i) adjust(i);
    }

    void adjust(int p)
    {
        int t = (p + tree.size()) >> 1;
        while(t > 0)
        {
            if(tree[t] == -1)
            {
                tree[t] = p;
                break;
            }
            else if(data[p] > data[tree[t]]) std::swap(p, tree[t]);
            t >>= 1;
        }
        tree[0] = p;
    }

    void update(T a)
    {
        data[tree[0]] = a;
        adjust(tree[0]);
    }

    // void display()
    // {
    //     std::cout << std::string(BUFFER_SIZE, ' ') << data[tree[0]].val << std::string(BUFFER_SIZE, ' ') << '\n';
    //     for(int i = 1, l = 1; i < tree.size();)
    //     {
    //         for(; i < (1 << l) && i < tree.size(); ++i)
    //         {
    //             std::cout << std::string(BUFFER_SIZE >> (l - 1), ' ')
    //                       << ((data[tree[i]].val == INT32_MAX) ? 0 : data[tree[i]].val)
    //                       << std::string(BUFFER_SIZE >> (l - 1), ' ');
    //         }
    //         std::cout << '\n';
    //         ++l;
    //     }
    // }

    T front() const { return data[tree[0]]; }
    int frontAddr() const { return tree[0]; }
};

struct FileIO
{
    std::fstream* file;
    int fileSize;

    FileIO(std::fstream& _file)
    {
        file = &_file;
        file->seekg(0, std::ios::end);
        fileSize = file->tellg();
    }

    void readData(std::ios_base::seekdir seekdir, int &offset, int size, std::vector<int> &v, int limit = INT32_MAX)
    {
        int num, cnt = 0;
        v.clear();
        file->seekg(offset, seekdir);
        for(; cnt < size && offset + sizeof(int) * cnt < std::min(fileSize, limit); ++cnt)
        {
            file->read(reinterpret_cast<char*>(&num), sizeof(int));
            v.push_back(num);
        }
        offset += sizeof(int) * cnt;
        ++accessCnt;
    }

    void writeData(std::ios_base::seekdir seekdir, int &offset, std::vector<int> &v)
    {
        file->seekp(offset, seekdir);
        for(auto a: v) file->write(reinterpret_cast<const char*>(&a), sizeof(int));;
        offset +=  sizeof(int) * v.size();
        v.clear();
        ++accessCnt;
    }
};

void createChunks(const std::string &filename, std::queue<int> &q)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if(!file)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }
    FileIO fio(file);

    int roff = 0, woff = 0;
    std::vector<int> data;
    std::vector<int> modi;
    std::vector<Point<int>> initChunk;
    fio.readData(std::ios::beg, roff, BUFFER_SIZE / 2, data);

    int seq = 1, i = 0, cnt = 0;
    LoserTree<Point<int>> lt;
    for(; i < BUFFER_SIZE / 4 && i < data.size(); ++i)
        initChunk.emplace_back(data[i], seq);
    for(; i < BUFFER_SIZE / 4; ++i)
        initChunk.emplace_back(INT32_MAX, INT32_MAX);
    lt.init(initChunk);

    for(seq = 0; true; ++cnt, ++i)
    {
        int t;
        if(i < data.size()) t = data[i];
        else if (roff < fio.fileSize)
        {
            fio.readData(std::ios::beg, roff, BUFFER_SIZE / 4, data);
            t = data[i = 0];
        }
        else t = INT32_MAX;

        Point<int> tmp = lt.front();
        if(cnt > 0 && (cnt % (BUFFER_SIZE / 4)) == 0 || tmp.val == INT32_MAX)
            fio.writeData(std::ios::beg, woff, modi);
        if(tmp.seq > seq)
        {
            q.push(sizeof(int) * cnt);
            ++seq;
        }
        if(tmp.val == INT32_MAX) break;

        modi.push_back(tmp.val);
        if(t < tmp.val) lt.update(Point<int>(t, seq + 1));
        
        else if (t == INT32_MAX) lt.update(Point<int>(t, INT32_MAX));
        else lt.update(Point<int>(t, seq));
    }

    file.close();
}

void externalSort(const std::string &filename, std::queue<int> &q)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if(!file)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }
    FileIO fio(file);

    while(q.size() > 2)
    {
        int woff = fio.fileSize, qs = q.size() - 1;
        std::vector<std::vector<int>> data(MERGE_WAYS);
        std::vector<std::pair<int, int>> roff; 
        for(int i = 0; i < MERGE_WAYS && i < qs; ++i)
        {
            int t = q.front();
            q.pop();
            roff.emplace_back(t, q.front());
        }

        std::vector<int> mergedChunk;
        std::vector<int> dataIndex(MERGE_WAYS, 1);
        std::vector<int> initChunk;
        LoserTree<int> lt;
        for(int i = 0; i < roff.size(); ++i)
        {
            fio.readData(std::ios::beg, roff[i].first, BUFFER_SIZE / (MERGE_WAYS + 1), data[i], roff[i].second);
            initChunk.push_back(data[i][0]);
        }
        lt.init(initChunk);

        while(true)
        {
            int tmp, ad = lt.frontAddr();
            if(dataIndex[ad] < data[ad].size()) tmp = data[ad][dataIndex[ad]++];
            else if(roff[ad].first < roff[ad].second)
            {
                fio.readData(std::ios::beg, roff[ad].first, BUFFER_SIZE / (MERGE_WAYS + 1), data[ad], roff[ad].second);
                tmp = data[ad][0];
                dataIndex[ad] = 1;
            }
            else tmp = INT32_MAX;
            mergedChunk.push_back(lt.front());
            lt.update(tmp);
            if(mergedChunk.size() == BUFFER_SIZE / (MERGE_WAYS + 1))
            {
                fio.writeData(std::ios::beg, woff, mergedChunk);
                fio.fileSize = woff;
            }
            if(lt.front() == INT32_MAX) break; 
        }

        fio.writeData(std::ios::beg, woff, mergedChunk);
        q.push(fio.fileSize = woff);
    }

    file.close();
}

void createChunksOutOfDate(const std::string &filename)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if(!file)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    int num;
    std::vector<int> data;
    std::vector<Point<int>> initChunk;
    while(file >> num)
        data.emplace_back(num);

    file.clear();
    file.seekp(0, std::ios::beg);

    int seq = 1, i = 0;
    LoserTree<Point<int>> lt;
    for(; i < BUFFER_SIZE / 4 && i < data.size(); ++i)
        initChunk.emplace_back(data[i], seq);
    for(; i < BUFFER_SIZE / 4; ++i)
        initChunk.emplace_back(INT32_MAX, seq);
    lt.init(initChunk);
    ++accessCnt; //初始化访存一次

    int cnt = 0;
    while(true)
    {
        int t = i < data.size() ? data[i++] : INT32_MAX; 
        Point<int> tmp = lt.front();
        if(tmp.val == INT32_MAX) break;
        if(tmp.seq > seq)
        {
            file << '\n';
            ++seq;
        }

        file << tmp.val << ' ';
        ++cnt;
        if(cnt >= BUFFER_SIZE / 4) cnt = 0, accessCnt += 2; //读数据 写数据

        if(t < tmp.val || t == INT32_MAX) lt.update(Point<int>(t, seq + 1));
        else lt.update(Point<int>(t, seq));
    }
    ++accessCnt; //最后一次写入

    file.close();
}

void externalSortOutOfDate(const std::string &filename)
{
    std::ifstream inFile(filename, std::ios::in | std::ios::out | std::ios::binary);
    if(!inFile)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    std::string s;
    std::vector<std::string> data;
    while(std::getline(inFile, s))
        data.emplace_back(s);
    inFile.close();

    std::vector<std::queue<int>> chunks(data.size());
    for(int i = 0; i < data.size(); ++i)
    {
        int num;
        std::stringstream ss;
        ss << data[i];
        while(ss >> num)
            chunks[i].emplace(num);
    }

    std::vector<std::queue<int>> temp;
    while(true)
    {
        int l = chunks.size();
        int s = l - std::min(l, MERGE_WAYS);
        int cnt = 0;
        std::vector<int> initChunk;
        LoserTree<int> lt;

        for(int i = s; i < l; ++i)
           cnt += (chunks[i].size() - 1) / (BUFFER_SIZE / (MERGE_WAYS + 1)) + 1;
        accessCnt += 2 * cnt; //写入 读取

        for(int i = s; i < l; ++i)
        {
            initChunk.emplace_back(chunks[i].front());
            chunks[i].pop();
            chunks[i].emplace(INT32_MAX);
        }
        lt.init(initChunk);

        std::queue<int> mergeChunk;
        while(true)
        {
            int t = chunks[s + lt.frontAddr()].front();
            if(t != INT32_MAX) chunks[s + lt.frontAddr()].pop();
            mergeChunk.emplace(lt.front());
            lt.update(t);
            if(lt.front() == INT32_MAX) break;
        }

        for(int i = s; i < l; ++i)
            chunks.pop_back();
        temp.emplace_back(mergeChunk);
        if(chunks.empty())
        {
            if(temp.size() == 1) break;
            chunks = temp;
            temp.clear();
        }
    }

    std::ofstream outFile(filename, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
    if(!outFile)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    while(!temp.front().empty())
    {
        outFile << temp.front().front() << ' ';
        temp.front().pop();
    }

    outFile.close();
}

void generateText(int offset = 0)
{
    const std::string filename = "storage.txt";
    const std::string outFilename = "storage.out";

    std::fstream inFile(filename, std::ios::in | std::ios::binary);
    if(!inFile)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }
    FileIO ifio(inFile);

    std::vector<int> data;
    ifio.readData(std::ios::beg, offset, INT32_MAX, data);
    inFile.close();

    std::fstream outFile(outFilename, std::ios::out | std::ios::binary | std::ios::trunc);
    if(!outFile)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    for(auto a: data) outFile << a << " ";
    outFile.close();
}

void generateRandomData(int size)
{
    static std::string filename = "storage.txt";
    static std::string backupFilename = "storage.backup";

    std::ofstream outFile(filename, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
    std::ofstream outBackup(backupFilename, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
    if(!outFile || !outBackup)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1e9);

    for(int i = 0; i < size; ++i)
    {
        int tmp = dis(gen);
        outFile.write(reinterpret_cast<const char*>(&tmp), sizeof(int));
        outBackup << tmp << " ";
    }

    outFile.close();
    outBackup.close();
}

bool compareAns()
{
    static std::string filename = "storage.out";
    static std::string backupFilename = "storage.backup";

    std::ifstream ansFile(filename, std::ios::in | std::ios::out | std::ios::binary);
    std::ifstream checkFile(backupFilename, std::ios::in | std::ios::out | std::ios::binary);
    if(!ansFile || !checkFile)
    {
        std::cerr << "无法打开文件！" << std::endl;
        return false;
    }

    int num;
    std::vector<int> chk;
    while(checkFile >> num)
        chk.push_back(num);
    
    checkFile.close();
    sort(chk.begin(), chk.end());

    std::vector<int>::const_iterator it = chk.begin();
    while(ansFile >> num)
    {
        if(it == chk.end() || *it != num)
        {
            ansFile.close();
            std::cout << num << '\n';
            std::cout << *it << '\n';
            return false;
        }
        ++it;
    }

    ansFile.close();
    return true;
}

int main()
{
    std::queue<int> chunkPos;

    generateRandomData(100000);
    createChunks("storage.txt", chunkPos);
    externalSort("storage.txt", chunkPos);
    if(compareAns()) std::cout << "YES\n";
    else std::cout << "NO\n";
    std::cout << accessCnt << '\n';
    
    generateText(chunkPos.front());

    return 0;
}