import React from "react";
import { useHistory } from "react-router-dom";

const Upload = () => {
    const history = useHistory();

    let recipe = {
        recipeName:"Japanese Meat and Potato Stew",
        description:"Japanese Meat and Potato Stew!!",
        ingredients:["potatoes","onions","carrots","chuck steak"],
        procedures:["chop everything", "blanch meat", "add everything and boil"],
        reviews:["00123", "32131"],
        userName:"Oscar Cheng",
        createdAt: Date.now,
    }

    const createRecipe = async (info) => {
      try{
        await fetch("/dashboard", {
          method: "POST",
          body: JSON.stringify(info),
          headers: {
            "Content-Type": "application/json",
          }
          }).then(res => {
          if (res.ok) {
            history.push("/dashboard");
            console.log("Frond-End Post Recipe Success")
          }
        })
      }
      catch(err){
        console.log("Front-End Post Recipe Fail");
      }
    };
    
    return(
        <div>
            <button onClick = {() => createRecipe(recipe)}>Recipe</button>
        </div>
    )
}

export default Upload;