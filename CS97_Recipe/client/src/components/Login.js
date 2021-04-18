import React from 'react';
import GoogleLogin from 'react-google-login';
import { useHistory } from "react-router-dom";

function Login() {
  const history = useHistory();
  
  const responseSuccessGoogle = async (googleData) => {
    await fetch("/auth/google", {
      method: "POST",
      body: JSON.stringify({ 
        token: googleData.tokenId
      }),
      headers: {
        "Content-Type": "application/json",
      }
    }).then(res => {
      if (res.ok) {
        // Clear localStorage and set localStorage
        localStorage.clear();
        localStorage.setItem('googleId', googleData.profileObj.googleId);
        localStorage.setItem('avatar', googleData.profileObj.imageUrl);
        localStorage.setItem('name', googleData.profileObj.name);
        localStorage.setItem('email', googleData.profileObj.email);
        localStorage.setItem('exp', googleData.tokenObj.expires_at);
        console.log("Google signin success");
        history.push("/dashboard");
      } else {
        console.log("Google signin fail");
      }
    })
  };

  const responseFailureGoogle = (res) => {
    console.log(res);
  };

  return (
    <div>
      <div className="text-center">
        <h1>Welcome to the Recipe App</h1>
        <p>Please login first to enter the website</p>
        <GoogleLogin
          clientId="281834657367-r6h4r3t5unmp2q9rl9usg3gp9k23iq3b.apps.googleusercontent.com"
          buttonText="Login With Google"
          onSuccess={responseSuccessGoogle}
          onFailure={responseFailureGoogle}
          cookiePolicy={'single_host_origin'}
        />
      </div>
    </div>
  );
}

export default Login;