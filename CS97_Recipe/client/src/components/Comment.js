import React from 'react'
import { makeStyles } from '@material-ui/core/styles';
import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import CardHeader from '@material-ui/core/CardHeader';
import Typography from '@material-ui/core/Typography';
import Avatar from '@material-ui/core/Avatar';

const useStyles = makeStyles({
    root: {
      minWidth: 275,
    },
});


function Comment(props) {
    const classes = useStyles();
    return (
        <div>
            <br />
            <h2 style={{ paddingLeft: 10 }}>Comments</h2>
            <hr />
            {props.CommentList && props.CommentList.map((comment, index) => (
                <Card className={classes.root} key={index}>
                    <CardHeader
                        avatar={
                        <Avatar aria-label="recipe">
                            {comment.userName.substring(0,1)}
                        </Avatar>
                        }
                        title={comment.userName}
                        subheader={comment.createdAt.substring(0, 10)}
                    />
                    <CardContent>
                        <Typography variant="body1" component="p">
                            {comment.message}
                        </Typography>
                    </CardContent>
                </Card>
            ))}
        </div >
    )
}
export default Comment;