import React from 'react'
import { withStyles } from '@material-ui/core/styles';
import TextField from '@material-ui/core/TextField';
import Button from '@material-ui/core/Button';

const useStyles = theme => ({
    root: {
        maxWidth: 'max',
    },
});

class CommentForm extends React.Component {
    constructor(props){
        super(props);
        this.state = this.getDefaultState();
    }
    
    getDefaultState = () => {
        return { comment: ''};
    }

    submit = async() => {
        console.log(this.state.comment)
        const info = {
            userName: localStorage.name,
            message: this.state.comment,
            recipeID: window.location.search.substring(4),
        }
        try{
            await fetch("/comment", {
                method: "POST",
                body: JSON.stringify(info),
                headers: {
                    "Content-Type": "application/json",
                }
                })
                .then(res => {
                    if (res.ok) {
                        window.location.reload()
                        console.log("Comment Success")
                }
            })
        }catch(err){
            console.log("Comment Fail");
        }
        this.setState(this.getDefaultState())
    }

    render() {
        const { classes } = this.props;
        
        return (
            <div className={classes.root} >
                <br />
                <h2 style={{ paddingLeft: 10 }}>Leave a comment!</h2>
                <form noValidate autoComplete="off">
                    <div>
                        <TextField
                            value={this.state.comment}
                            id="outlined-multiline-static"
                            label="Comment"
                            fullWidth
                            multiline
                            rows={4}
                            variant="outlined"
                            onChange={(e)=>{this.setState({comment: e.target.value})}}
                        />
                        <Button variant="contained" color="primary" onClick={() => this.submit()}>Submit</Button>
                    </div>
                </form>
            </div >
        )
    }
}

export default withStyles(useStyles)(CommentForm)