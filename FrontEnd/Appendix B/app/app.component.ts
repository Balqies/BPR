import { Component, ViewChild } from '@angular/core';
import { HttpClient, HttpParams, HttpHeaders, HttpResponse } from '@angular/common/http';
import { Post } from './post';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent
 {
  openSidenav = false;

  readonly url = 'https://jsonplaceholder.typicode.com'; // no spaces between ' and url

  posts: Observable<Post[]>;

  constructor(private http: HttpClient){ }
  
//// POST method
  createPost()
  {
	  cosnt data: Post = {
		  id : null,
		  userId: 23,
		  title: 'new post',
		  body: 'dummy post'
	  
	  this.newPost = this.http.post(this.url + '/posts', data)
  }


  //////  test api get data
  getdata()
  {
    let headers = new HttpHeaders().set('Authorization', 'auth-token'); 

    this.posts = this.http.get(this.url + '/posts' );
  }

//////
  //getdata(){ //  send request error 401
  //  const httpHeaders = new HttpHeaders({
  //    'content-type': 'application/jason',
  //    'Authorization' : '75304e8d14ff4032afd37733340e01a1'
  //  })
   // return this.posts = this.http.get('https://moviesfinal.azure-api.net/v1/api/Avaliabilities' + '/posts' , {headers : httpHeaders  })
 // }

 //getdata() //401
 //{
 // const httpheaders = new HttpHeaders({
    // 'content-type': 'application/jason',
    //   'Ocp-Apim-Subscription-Key' : '75304e8d14ff4032afd37733340e01a1'
    //  });
    //  this.posts = this.http.get(this.url + '/posts' );


    //////
   //getdata(){ // 401
    // let headers = new HttpHeaders();
     //let other_header = headers.set('Ocp-Apim-Subscription-Key', '75304e8d14ff4032afd37733340e01a1');
    //let url = 'https://moviesfinal.azure-api.net/v1/api/Avaliabilities' + '/posts';
   // this.http.get(url, {headers: other_header}).subscribe(
     // res => console.log('handle your response', res),
     // msg => console.error(`Error: ${msg.status} ${msg.statusText}`)
    //);
  // }

  



      

 }


  



//Endpoint test: https://jsonplaceholder.typicode.com 
//Endpoint: https://moviesfinal.azure-api.net/v1/api/Avaliabilities
// auth key: 75304e8d14ff4032afd37733340e01a1


///// Unsuccessful tries ///////
/// doesnt work
//getLoggedInUser(auth_token): Observable<any> {
    //const headers = new Headers({
      //'Content-Type': 'application/json',
      //'Authorization': `75304e8d14ff4032afd37733340e01a1`
    //})
    //this.posts = this.http.get(this.url + '/posts', {headers});
    //return this.posts;
  //}

//////
//getdata(){ // doesnt send request
  //  const httpHeaders = new HttpHeaders({
   //   'content-type': 'application/jason',
   //   'Authorization' : '75304e8d14ff4032afd37733340e01a1'
   // })

  //  return this.http.get('https://moviesfinal.azure-api.net/v1/api/Avaliabilities' , {headers : httpHeaders  })

//  }