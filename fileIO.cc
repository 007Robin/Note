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
