const express = require('express');
const {cpp} = require('compile-run');
const cors = require('cors');
const bodyParser = require('body-parser');
const fs = require('fs');
const app = express();

app.use(bodyParser.json());

app.use(cors({
  origin: true,
  exposedHeaders: ['Content-Length', 'X-Foo', 'X-Bar'],
  credentials: true,
}));

var trace;

app.post('/', (req, res) => {

  let inp = req.body.n + " " + req.body.m + " " + req.body.x + " " + req.body.y;
  cpp.runFile('LOI_Final.cpp', {stdin: inp, compileTimeout:10000}, (err, result) => {
    if(err){
        console.log(err);
    }
    else{
          trace = result.stdout;
          fs.writeFile(__dirname + '/' + "xyz.txt", result.stdout, function (err) {
            if (err) {
                console.log('An error occured while writing JSON Object to File.\n' + err);
            }
            console.log('Access control JSON file has been saved.');
          });
          let out = trace.split("\n");
          res.status(200).json({
            ans: out
          });
      }
    });
  }
)

// Launch the server on port 3000
const server = app.listen(process.env.PORT || 3001, () => {
  const { address, port } = server.address();
  console.log(`Listening at http://${address}:${port}`);
});