import React, { useEffect, useState } from "react";
import {useHistory} from 'react-router-dom';
import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import CardHeader from '@material-ui/core/CardHeader';
import Typography from '@material-ui/core/Typography';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from "@material-ui/core/Toolbar";
import IconButton from '@material-ui/core/IconButton';
import HomeIcon from '@material-ui/icons/Home';
import ExitToAppIcon from '@material-ui/icons/ExitToApp';
import Grid from '@material-ui/core/Grid';

import Comment from "./Comment.js"
import CommentForm from "./CommentForm.js"

function Recipe() {
    const [recipe, setRecipe] = useState(null);
    const [commentList, setCommentList] = useState(null);
    const history = useHistory();

    const logout = () => {
        localStorage.clear();
        history.push("/");
    }

    const dashboard = () => {
        history.push("/dashboard");
    }

    const fetchRecipe = async () => {
        await fetch(`/recipe${window.location.search}`)
        .then(res => res.json())
        .then(data => {
            setRecipe(data);
            console.log(data)
        });
    }

    const fetchComment = async() => {
        await fetch(`/comment${window.location.search}`)
        .then(res => res.json())
        .then(data => {
            setCommentList(data);
        });
    }
    
    useEffect(()=>{
        fetchRecipe();
        fetchComment();
    }, [])

    return (
        <div>
            <AppBar position="static">
                <Toolbar>
                    <Grid
                        justify="space-between" // Add it here :)
                        container
                        spacing={10}
                    >
                        <Grid item>
                            <IconButton color="inherit" onClick={() => dashboard()}>
                                <HomeIcon />
                                Dashboard
                            </IconButton>
                        </Grid>
                        <Grid item>
                        <IconButton color="inherit"  edge="end" onClick={() => logout()}>
                            <ExitToAppIcon />
                            Logout
                        </IconButton>
                        </Grid>
                    </Grid>
                </Toolbar>
            </AppBar>
            <div>
                {recipe && recipe.map((recipe, index) => (
                    <Card key={index}>
                        <CardHeader
                            title={recipe.recipeName}
                            subheader={"by " + recipe.userName + ", " + recipe.createdAt.substring(0, 10)}
                        />
                        <CardContent>
                            <Typography variant="h5" component="p">
                                Ingredients:
                            </Typography>
                            <Typography variant="body1" component="p">
                                {recipe.ingredients}
                            </Typography>
                            <br />
                            <Typography variant="h5" component="p">
                                Procedures:
                            </Typography>
                            <Typography variant="body1" component="p" style={{ whiteSpace: "pre-line" }}>
                                {recipe.procedures.split("<br/>").join("\n")}
                            </Typography>
                        </CardContent>
                    </Card>
                ))}
            </div>
            <Comment CommentList={commentList}/>
            <CommentForm />
        </div >
    );
}

export default Recipe;