//
//  ExampleApplicationViewController.m
//  Junaio Plugin
//
//  Created by Stefan Misslinger on 3/15/11.
//  Copyright 2011 metaio, Inc. All rights reserved.
//


#import "ExampleApplicationViewController.h"
#import "ARViewController.h"


@implementation ExampleApplicationViewController


- (IBAction)onStartPushed:(id)sender
{
    // Create a new ARViewController. All channel details and properties are defined in that class.
    // see ARViewController.mm for the implementation
    ARViewController* junaioPlugin = [[ARViewController alloc] init];
    
    // present the viewcontroller
    [self presentModalViewController:junaioPlugin animated:YES];
    
    // release it, because it's retained as modalViewController
    [junaioPlugin release];
}

- (IBAction)onStartPushed2:(UIButton *)sender {
    // Create a new ARViewController. All channel details and properties are defined in that class.
    // see ARViewController.mm for the implementation
    ARViewController* junaioPlugin = [[ARViewController alloc] init];
    
    // present the viewcontroller
    [self presentModalViewController:junaioPlugin animated:YES];
    
    // release it, because it's retained as modalViewController
    [junaioPlugin release];

}


- (void)dealloc {
    [super dealloc];
}
- (void)viewDidUnload {
    [super viewDidUnload];
}



@end
