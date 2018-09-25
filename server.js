const express = require('express');
const {cpp} = require('compile-run');
const cors = require('cors');
const bodyParser = require('body-parser');
const fs = require('fs');
const app = express();

app.use(bodyParser.json());
// app.use(function (req, res, next) {
//   res.setHeader('Access-Control-Allow-Origin', 'http://localhost:3000');
//   res.setHeader('Access-Control-Allow-Methods', 'GET');
//   res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');
//   res.setHeader('Access-Control-Allow-Credentials', true);
//   next();
// });
app.use(cors({
  origin: true,
  exposedHeaders: ['Content-Length', 'X-Foo', 'X-Bar'],
  credentials: true,
}));


const sourcecode = `#include<iostream>
using namespace std;
int main(){
	printf("HEllp");
	return 0;
}`

var trace;

// Handle / route
app.post('/', (req, res) => {

  console.log(req.body.x);
//  res.send(req.dimensions);
  let inp = req.body.x + " " + req.body.y + " " + req.body.dimensions;
  console.log(inp);
  cpp.runFile('G:\\LOI-code2.cpp', {stdin: inp, compileTimeout:10000}, (err, result) => {
    if(err){
        console.log(err);
    }
    else{
    //      console.log("HI");
    //      console.log(result.stdout);
          trace = result.stdout;
          fs.writeFile(__dirname + '/' + "xyz.txt", result.stdout, function (err) {
            if (err) {
                console.log('An error occured while writing JSON Object to File.\n' + err);
            }
            console.log('Access control JSON file has been saved.');
          });
          let out = trace.split("\n");
          console.log(out[0]);

          res.status(200).json({
            ans: out
          });
      }
    });
  }
)

// Launch the server on port 3000
const server = app.listen(4000, () => {
  const { address, port } = server.address();
  console.log(`Listening at http://${address}:${port}`);
});