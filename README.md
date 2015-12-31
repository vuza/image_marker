# image_marker
Web application to mark objects on images.

## development

### Git flow
This repo uses (at least is trying to) git flow, stick to the rules: http://nvie.com/posts/a-successful-git-branching-model/

### Semver
The webapp (client and frontend) is using Semantic Versioning (http://semver.org/), be sure to update version in package.json correctly.

## deployment
App can be deployed through ansible, run:
```
ansible-playbook deployment/playbook.yml --ask-pass --ask-sudo -u <your-user>
```
You can omit the -u parameter if your local user is equal to remote user at alagoda.at 
The script installs the app at alagoda.at, the frontend is reachable via im.alagoda.at