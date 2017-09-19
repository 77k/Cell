#ifndef BLIF_PARSER
#define BLIF_PARSER

struct BLIFParser
{

	struct {
		std::string model, inputs, outputs, names, clock;
	} current;

	BLIFParser(){};
	BLIFParser(std::string filename){ current.model = filename; };

	std::map< std::string, std::function< void (std::string&) > >
		_map = {
			{"model", [&](std::string &s){

							     current.model = s;
							     std::cout << "beg model: "
								     << std::endl
								     << s << std::endl <<  "end model. "
								     << std::endl;}
			},
			{"inputs", [&](std::string &s){
							      //boost::regex names {"\\s[([A-Za-z0-9\\(\\)]+)\\s]*"};
							      //boost::regex names {"([A-Za-z0-9\\(\\)]+\\s)"};
							      boost::regex names {"\\s+"};
							      boost::smatch matches;
							      boost::sregex_token_iterator i(s.begin(), s.end(), names, -1);
							      boost::sregex_token_iterator e;
							      std::vector< std::string > input_names;
							      while(i != e)
							      {
								      std::cout << " in : " << *i++;
								      // input_names.push_back(*i++);
							      }
							      /* 
								 for(auto m: matches)
								 {
								 std::cout << "matches " << std::string(m) << std::endl;
								 input_names.push_back(m);
								 }
								 input_names.erase(input_names.begin());
							       */
							      for(auto m: input_names) { std::cout << " in : " << m; }
							     std::cout << std::endl;
							     std::cout << "beg inputs: "
								       << std::endl
								       << s
								       << std::endl
								       << "end inputs. " << std::endl;}
			},
			{"outputs", [&](std::string &s){
							     std::cout << "beg output: "
								       << std::endl
								       << s
								       << std::endl
								       <<  "end outputs. " << std::endl;}
			},
			{"names", [&](std::string &s){
							     std::cout << "beg names: "
							       	       << std::endl
							 	       << s
								       << std::endl
								       <<  "end names. " << std::endl;}
			},
			{"clock", [&](std::string &s){
							     std::cout << "beg clock: "
								       << std::endl
								       << s
								       << std::endl
								       <<  "end clock. " << std::endl;}
			},
			{"end", [&](std::string &s){
							     std::cout << "beg end: "
								       << std::endl
								       << s
								       << std::endl
								       <<  "end end. " << std::endl;}
			},

		};

	std::function < void (std::string&) > operator [](const   std::string s)
	{
		std::cout << "Current State: " << std::endl
			<< "model: " << current.model << " inputs: " <<   current.inputs << " outputs: " << current.outputs
			<< " names: " << current.names << " clock: " <<   current.clock << std::endl;
		if([&]() { return _map.find(s);}() == _map.end())
		{
			std::cout << "." << s << " not defined." <<   std::endl;
			return [&](std::string &_s){ std::cout <<     "don't kno' " << _s
				<<     std::endl;
			};
		}
		return _map[s];
	}

	std::istream& operator << (std::istream &is)
	{
		boost::regex backslash {"[\\.A-Za-z0-9\\)\\(\\s]+     \\\\"};
		boost::regex decl {"\\.([A-Za-z0-9]+)\\s+([A-Za-z0-   9\\(\\)\\s]*).*"};

		std::cout << "Begin Parsing of Filename: " << current.model << std::endl;
		std::string res_line, line;
		while(!is.eof())
		{
			boost::smatch matches;
			res_line.clear(); line.clear();
			for(;;)
			{
				std::getline(is, line);
				res_line += line;
				if(!boost::regex_match(line, matches,         backslash)) break;
			}
			res_line.erase(std::remove(res_line.begin(),      res_line.end(), '\\'), res_line.end());
			std::cout << "res_line: " << res_line << std::    endl;
			if(boost::regex_match(res_line, matches, decl))
			{
				std::cout << "matches[1] = " << matches[1] << std::endl;
				std::string meh = matches[2];
				(*this)[matches[1]](meh);
			}
		}
		return is;
	}

};
#endif

