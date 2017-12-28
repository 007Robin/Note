 void ReadFileToVec(const string& filename, vector<string>& vec) {
     ifstream ifs(filename);
     if(ifs) {
          string buf;
          while(geline(ifs, buf)){      
              vec.push_back(buf);
          }   
      }
  }
  
 void ReadFileToVec(const string& filename, vector<string>& vec) { 
      ifstream ifs(filename);
      if(ifs){
          string buf;
          while(isf >> buf)           
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
