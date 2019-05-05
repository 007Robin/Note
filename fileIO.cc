#include<fstream>

void ReadFileToVec(const string& filename, vector<string>& vec) {
     ifstream ifs(filename);
     if(ifs) {
          string buf;
          while(geline(ifs, buf)){      //一行一行存在vec里
              vec.push_back(buf);
          }   
      }
  }
  
 void ReadFileToVec(const string& filename, vector<string>& vec) { 
      ifstream ifs(filename);
      if(ifs){
          string buf;
          while(isf >> buf)           //一个词一个词存在vec里
              vec.push_back(buf);
      }
  }

void write(string fileName){
     ofstream out(fileName);
     if(out) {
	 auto n = fileName.find('.');
	 string s = fileName.substr(0, n);
	 out << "solid " << s << endl;
	 for( int i = 0; i < shapes.size(); ++i) {
		 shapes[i]->write(out);
	 }
	 out << "endsolid " << s;
	 out.close();
     }
}

//exe in command line$: ./a.out filename1 filename2 filename3
int main(int argc, char* argv[]) {
	vector<string> v;
	ReadFileToVec(argv[1], v);
	ReadFileToVec(argv[2], v);
	write(argv[3]);
	return 0;
}
